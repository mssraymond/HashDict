#ifndef HASHDICT_HPP
#define HASHDICT_HPP

#include <iostream>

class HashException : public std::exception
{
private:
    std::string message;

public:
    explicit HashException(const std::string &msg) : message(msg) {}

    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

class HashNode
{
private:
public:
    HashNode(const std::string &key, void *val, const std::string &type);
    ~HashNode();
    std::string key;  // Data's key
    void *val;        // Data's value
    std::string type; // Data type
    HashNode *next;   // Pointer to next node
    void print();     // Prints node
};

class BucketNode
{
private:
public:
    BucketNode(int id);
    ~BucketNode();
    int chain;
    int id;
    HashNode *node;
};

class HashDict
{
private:
    int size = 10;
    BucketNode **buckets;
    int hashFunc(const std::string &key);
    HashNode *find(const std::string &key, const bool &del);
    std::optional<std::variant<char, std::string, int, float, bool>> conditionalReturn(HashNode *node);

public:
    HashDict(int size = 0);
    ~HashDict();
    void put(const std::string &key, void *val, const std::string &type);
    std::pair<void *, std::string> get(const std::string &key);
    std::pair<void *, std::string> pop(const std::string &key);
    void print();
    char getChar(std::pair<void *, std::string> pair);
    std::string getStr(std::pair<void *, std::string> pair);
    int getInt(std::pair<void *, std::string> pair);
    float getFloat(std::pair<void *, std::string> pair);
    bool getBool(std::pair<void *, std::string> pair);
};

#endif