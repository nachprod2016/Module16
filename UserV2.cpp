#include <iostream>
#include <vector>
#include <cstdlib>
#include "UserV2.h"

User::User(std::string login) : _login(login){}

User::~User(){}

void User::addChat(std::string name, std::list<Chat>::iterator chat)
{
    std::pair<std::string, std::list<Chat>::iterator> newPair = std::make_pair(name, chat);
    contacts.insert(newPair);
}

bool User::checkContact(std::string name)
{
    bool flag = false;
    if (contacts.find(name) != contacts.end())
    {
        flag = true;
    }
    return flag;
}

void User::writeMessage()
{
    size_t n = 0;
    size_t size = contacts.size();
    std::vector<std::string>logins(size);
    std::map<std::string, std::list<Chat>::iterator>::iterator start = contacts.begin();
    std::map<std::string, std::list<Chat>::iterator>::iterator end = contacts.end();
    for (start; start != end; start++)
    {
        std::string login = start->first;
        logins[n] = login;
        std::cout << n << " - " << logins[n] << std::endl;
        n++;
    }
    std::string choice;
    std::cout << "Введите номер контакта: ";
    std::cin >> choice;
    if (choice.size() > 9)
    {
        std::cout << "Ошибка ввода!" << std::endl;
        std::cout << "Введите любой символ для продолжения: ";
        std::cin >> choice;
        return;
    }
    int num;
    if (choice == "0")
    {
        num = 0;
    }
    else
    {
        num = atoi(&choice[0]);
        if (num == 0 || num < 0 || num >= n)
        {
            std::cout << "Ошибка ввода" << std::endl;
            std::cout << "Введите любой символ для продолжения: ";
            std::cin >> choice;
            return;
        }
    }
    std::map<std::string, std::list<Chat>::iterator>::iterator contact = contacts.find(logins[num]);
    while (true)
    {
        system("clear");
        contact->second->showMessages();
        std::cout << "Ваше сообщение: ";
        std::getline(std::cin, choice);//очистка потока ввода
        std::getline(std::cin, choice);//ввод сообщения
        Message newMessage(_login, choice);
        contact->second->addMessage(newMessage);
        std::cout << "Продолжить?" << std::endl;
        std::cout << "1 - Да" << std::endl;
        std::cout << "2 - Нет" << std::endl;
        std::cin >> choice;
        if (choice != "1")
        {
            break;
        }
    }
}

void User::writeAll()
{
    if (contacts.size() == 0)
    {
        return;
    }
    std::string choice;
    system("clear");
    std::cout << "Ваше сообщение: ";
    std::getline(std::cin, choice);//очистка потока ввода
    std::getline(std::cin, choice);//ввод сообщения
    Message newMessage(_login, choice);
    std::map<std::string, std::list<Chat>::iterator>::iterator begin = contacts.begin();
    std::map<std::string, std::list<Chat>::iterator>::iterator end = contacts.end();
    for (begin; begin != end; begin++)
    {
        begin->second->addMessage(newMessage);
    }
}