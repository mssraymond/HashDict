#include <iostream>
#include "HashDict.hpp"

void printOptionalVariant(std::optional<std::variant<char, std::string, int, float, bool>> x)
{
    if (x.has_value())
    {
        std::visit(
            [](auto &&arg)
            {
                std::cout << arg << std::endl;
            },
            x.value());
    }
}

int main()
{
    HashDict dict = HashDict();
    dict.print();

    dict.put("Apple", new float(252.2), "float");
    dict.put("Amazon", new float(221.3), "float");
    dict.put("Google", new float(192.69), "float");
    dict.put("Meta", new float(591.24), "float");
    dict.put("Netflix", new float(900.43), "float");
    dict.put("Microsoft", new float(424.83), "float");
    dict.put("Discord", new std::string("NA"), "str");

    dict.put("Onsmble", new int(0), "int");
    dict.put("Bluetree", new std::string("NULL"), "str");

    dict.put("Atlassian", new float(247.1), "float");
    dict.put("DoorDash", new float(169.6), "float");

    dict.put("OpenAI", new std::string("NA"), "str");
    dict.put("Anthropic", new std::string("NA"), "str");
    dict.put("xAI", new std::string("NA"), "str");
    dict.put("Anduril", new std::string("NA"), "str");

    dict.put("NVIDIA", new float(137.49), "float");
    dict.put("TSMC", new float(200.39), "float");

    dict.put("SureCo", new std::string("NA"), "str");
    dict.put("Northrop Grumman", new float(466.52), "float");

    dict.put("Tesla", new float(417.51), "float");
    dict.put("ServiceNow", new float(1067.70), "float");

    dict.put("SpaceX", new std::string("NA"), "str");

    dict.print();

    dict.put("Discord", new std::string("PENDING"), "str");
    dict.put("OpenAI", new std::string("N/A"), "str");
    dict.put("Anthropic", new std::string("N/A"), "str");
    dict.put("xAI", new std::string("N/A"), "str");
    dict.put("Anduril", new std::string("N/A"), "str");
    dict.put("SureCo", new std::string("NONE"), "str");
    dict.put("SpaceX", new std::string("N/A"), "str");

    dict.print();

    dict.put("Disney", new float(100.0), "float");
    dict.put("Disney", new float(110.80), "float");

    dict.print();

    dict.put("Bull Market", new bool(false), "bool");

    dict.print();

    dict.put("Bull Market", new bool(true), "bool");

    dict.print();

    std::cout << dict.getFloat(dict.get("Northrop Grumman")) << std::endl;
    std::cout << dict.getStr(dict.pop("SureCo")) << std::endl;
    std::cout << dict.getStr(dict.pop("Bluetree")) << std::endl;
    std::cout << dict.getFloat(dict.get("DoorDash")) << std::endl;
    std::cout << dict.getFloat(dict.get("Atlassian")) << std::endl;
    std::cout << dict.getInt(dict.pop("Onsmble")) << std::endl;
    std::cout << dict.getStr(dict.pop("Discord")) << std::endl;

    dict.print();

    HashDict newDict = HashDict(5);
    newDict.print();
    newDict.put("Bear Market", new bool(false), "bool");
    newDict.put("Bull Market", new bool(true), "bool");
    newDict.put("Modulo", new char('%'), "char");
    newDict.put("Ampersand", new char('&'), "char");
    newDict.print();
    std::cout << newDict.getChar(newDict.get("Modulo")) << std::endl;
    std::cout << newDict.getBool(newDict.pop("Bear Market")) << std::endl;
    newDict.print();

    return 0;
}