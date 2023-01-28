#pragma once
#include <vector>
#include <map>
#include <string>
#include <list>
#include <iterator>
#include "ChatV2.h"

class User
{
private:
    std::string _login;
    std::map<std::string, std::list<Chat>::iterator> contacts;
public:
    User(std::string login);
    ~User();
    void addChat(std::string name, std::list<Chat>::iterator chat);
    bool checkContact(std::string name);
    void writeMessage();
    void writeAll();
};