#include "HashDict.hpp"

HashNode::HashNode(const std::string &key, void *val, const std::string &type)
{
    this->key = key;
    this->val = val;
    this->type = type;
    this->next = nullptr;
}

HashNode::~HashNode()
{
}

void HashNode::print()
{
    if (this->type == "char")
    {
        std::cout << "(key: " << this->key << ", val: " << *(char *)this->val << ", type: " << this->type << ")" << std::flush;
    }
    else if (this->type == "str")
    {
        std::cout << "(key: " << this->key << ", val: " << (char *)this->val << ", type: " << this->type << ")" << std::flush;
    }
    else if (this->type == "int")
    {
        std::cout << "(key: " << this->key << ", val: " << *(int *)this->val << ", type: " << this->type << ")" << std::flush;
    }
    else if (this->type == "float")
    {
        std::cout << "(key: " << this->key << ", val: " << *(float *)this->val << ", type: " << this->type << ")" << std::flush;
    }
    else if (this->type == "bool")
    {
        std::cout << "(key: " << this->key << ", val: " << std::boolalpha << *(bool *)this->val << ", type: " << this->type << ")" << std::flush;
    }
    if (this->next == nullptr)
    {
        std::cout << std::endl;
    }
}

BucketNode::BucketNode(int id)
{
    this->chain = 0;
    this->id = id;
    this->node = nullptr;
}

BucketNode::~BucketNode()
{
}

HashDict::HashDict(int size)
{
    if (size > 0)
    {
        this->size = size;
    }
    this->buckets = new BucketNode *[this->size];
    for (int i = 0; i < this->size; i++)
    {
        this->buckets[i] = new BucketNode(i);
    }
}

HashDict::~HashDict()
{
}

int HashDict::hashFunc(const std::string &key)
{
    std::hash<std::string> hf;
    return hf(key) % this->size;
}

void HashDict::put(const std::string &key, void *val, const std::string &type)
{
    int hashKey = this->hashFunc(key);
    BucketNode *bucket = this->buckets[hashKey];
    if (bucket->node == nullptr)
    {
        HashNode *node = new HashNode(key, val, type);
        bucket->node = node;
        if (bucket->chain < 1)
        {
            bucket->chain = 1;
        }
        std::cout << "Added " << key << " to bucket " << hashKey << std::endl;
    }
    else
    {
        HashNode *tmp = bucket->node;
        while (tmp != nullptr)
        {
            if (key == tmp->key) // Match found; update
            {
                tmp->val = val;
                tmp->type = type;
                std::cout << "Updated " << key << " in bucket " << hashKey << std::endl;
                break;
            }
            else // Iterate
            {
                if (tmp->next == nullptr) // Match NOT found; append
                {
                    HashNode *node = new HashNode(key, val, type);
                    tmp->next = node;
                    bucket->chain++;
                    std::cout << "Added " << key << " to bucket " << hashKey << std::endl;
                    break;
                }
                else // Continue to iterate
                {
                    tmp = tmp->next;
                }
            }
        }
    }
}

HashNode *HashDict::find(const std::string &key, const bool &del = false)
{
    int hashKey = this->hashFunc(key);
    if (this->buckets[hashKey] == nullptr)
    {
        return nullptr;
    }
    else
    {
        HashNode *node = this->buckets[hashKey]->node;
        HashNode *prev = nullptr;
        while (node != nullptr)
        {
            if (node->key == key) // Match found!
            {
                if (!del)
                {
                    std::cout << "Found " << key << " at bucket " << hashKey << " with " << node->type << " value " << std::flush;
                }
                else
                {
                    if (prev == nullptr) // Node at head
                    {
                        this->buckets[hashKey]->node = node->next; // Remove node from head
                    }
                    else // Node NOT at head
                    {
                        prev->next = node->next; // Remove node from chain
                    }
                    this->buckets[hashKey]->chain--;
                    std::cout << "Removed " << key << " from bucket " << hashKey << " with " << node->type << " value " << std::flush;
                }
                return node;
            }
            else
            {
                prev = node;
                node = node->next;
            }
        }
        return nullptr;
    }
}

std::optional<std::variant<char, std::string, int, float, bool>> HashDict::conditionalReturn(HashNode *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->type == "char")
    {
        return *(char *)node->val;
    }
    if (node->type == "str")
    {
        return (char *)node->val;
    }
    if (node->type == "int")
    {
        return *(int *)node->val;
    }
    if (node->type == "float")
    {
        return *(float *)node->val;
    }
    if (node->type == "bool")
    {
        return *(bool *)node->val;
    }
    return nullptr;
}

std::pair<void *, std::string> HashDict::get(const std::string &key)
{
    HashNode *node = this->find(key);
    return {node->val, node->type};
}

std::pair<void *, std::string> HashDict::pop(const std::string &key)
{
    HashNode *node = this->find(key, true);
    return {node->val, node->type};
}

void HashDict::print()
{
    std::cout << "----------" << std::endl;
    int longestChain = 0;
    for (int i = 0; i < this->size; i++)
    {
        BucketNode *bucket = this->buckets[i];
        if (bucket->chain > longestChain)
        {
            longestChain = bucket->chain;
        }
        std::cout << "Bucket: " << bucket->id << std::endl;
        HashNode *node = bucket->node;
        while (node != nullptr)
        {
            node->print();
            node = node->next;
            if (node != nullptr)
            {
                std::cout << " => " << std::flush;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Longest Chain: " << longestChain << " node(s)" << std::endl
              << "----------"
              << std::endl;
}

char HashDict::getChar(std::pair<void *, std::string> pair)
{
    if (pair.second == "char")
    {
        return *(char *)pair.first;
    }
    else
    {
        throw HashException("Must be `char` data type");
    }
}

std::string HashDict::getStr(std::pair<void *, std::string> pair)
{
    if (pair.second == "str")
    {
        return (char *)pair.first;
    }
    else
    {
        throw HashException("Must be `str` data type");
    }
}

int HashDict::getInt(std::pair<void *, std::string> pair)
{
    if (pair.second == "int")
    {
        return *(int *)pair.first;
    }
    else
    {
        throw HashException("Must be `int` data type");
    }
}

float HashDict::getFloat(std::pair<void *, std::string> pair)
{
    if (pair.second == "float")
    {
        return *(float *)pair.first;
    }
    else
    {
        throw HashException("Must be `float` data type");
    }
}

bool HashDict::getBool(std::pair<void *, std::string> pair)
{
    if (pair.second == "bool")
    {
        return *(bool *)pair.first;
    }
    else
    {
        throw HashException("Must be `bool` data type");
    }
}