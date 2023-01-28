#include <iterator>
#include <iostream>
#include "ChatV2.h"

Chat::Chat(){};

Chat::~Chat(){};

void Chat::addMessage(Message & m)
{
    messages.push_back(m);
}

void Chat::showMessages()
{
    std::list<Message>::iterator begin = messages.begin();
    std::list<Message>::iterator end = messages.end();
    for (begin; begin != end; begin++)
    {
        std::cout << begin->getAuthor() << ": " << begin->getMessage() << std::endl;
    }
}