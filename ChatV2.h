#pragma once
#include <list>
#include "Message.h"


class Chat
{
private:
    std::list<Message> messages;
public:
    Chat();
    ~Chat();
    void addMessage(Message & m);
    void showMessages();
};