#pragma once
#include <map>
#include <list>
#include <string>
#include "ChatV2.h"
#include "UserV2.h"

class Server
{
private:
    bool chatWork;
    std::map<std::string, std::string> authorizationData;
    std::map<std::string, User> users;
    std::list<Chat> chats;
    std::string adminLogin;
    std::string adminPassword;
public:
    Server();
    ~Server();
    void work();
    void registration();
    std::map<std::string, User>::iterator authorization(std::string login, std::string password);
    void adminSession();
    void userSession(std::map<std::string, User>::iterator);
};