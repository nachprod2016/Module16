#include <iostream>
#include <iterator>
#include "ServerV2.h"

Server::Server() : chatWork(true)
{
    std::cout << "Создание учетной записи администратора" << std::endl;
    std::cout << "Логин: ";
    std::cin >> adminLogin;
    std::cout << "Пароль: ";
    std::cin >> adminPassword;
};

Server::~Server(){};

void Server::work()
{
    std::string choice;
    while (chatWork)
    {
        system("clear");
        std::cout << "1 - Регистрация" << std::endl;
        std::cout << "2 - Вход" << std::endl;
        std::cout << "Ввод: ";
        std::cin >> choice;
        if (choice == "1")
        {
            registration();
        }
        else if (choice == "2")
        {
            std::string login;
            std::string password;
            std::cout << "Логин: ";
            std::cin >> login;
            std::cout << "Пароль: ";
            std::cin >> password;
            if (login == adminLogin && password == adminPassword)
            {
                adminSession();
            }
            else
            {
                std::map<std::string, User>::iterator it = authorization(login, password);
                if (it == users.end())
                {
                    std::cout << "Неверный логин или пароль" << std::endl;
                    std::cout << "Введите любой символ для продолжения: ";
                    std::cin >> login;
                }
                else
                {
                    userSession(it);
                }
            }
        }
    }
}

void Server::registration()
{
    system("clear");
    std::string login;
    std::string password;
    std::cout << "Создание новой учетной записи" << std::endl;
    std::cout << "Логин: ";
    std::cin >> login;
    if (users.find(login) != users.end() || login == adminLogin)
    {
        std::cout << "Пользователь с таким логином уже зарегестрирован!" << std::endl;
        std::cout << "Введите любой символ для продолжения: ";
        std::cin >> login;
        return;
    }
    std::cout << "Пароль: ";
    std::cin >> password;
    User user(login);
    std::pair<std::string, std::string> autoData = std::make_pair(login, password);
    authorizationData.insert(autoData);
    std::pair<std::string, User> newUser = std::make_pair(login, user);
    users.insert(newUser);
    system("clear");
}

std::map<std::string, User>::iterator Server::authorization(std::string login, std::string password)
{
    std::map<std::string, std::string>::iterator it = authorizationData.find(login);
    if (it != authorizationData.end() && it->second == password)
    {
        return users.find(it->first);
    }
    else
    {
        return users.end();
    }
}

void Server::userSession(std::map<std::string, User>::iterator user1)
{
    std::string choice;
    while (true)
    {
        system("clear");
        std::cout << "1 - Добавить новый контакт" << std::endl;
        std::cout << "2 - Написать сообщение" << std::endl;
        std::cout << "3 - Написать всем из списка контактов" << std::endl;
        std::cout << "0 - Выйти из учетной записи" << std::endl;
        std::cin >> choice;
        if (choice == "1")
        {
            std::cout << "Введите логин собеседника: ";
            std::cin >> choice;
            std::map<std::string, User>::iterator user2 = users.find(choice);
            if (user2 == users.end())
            {
                std::cout << "Пользователь с таким логином не зарегестрирован." << std::endl;
                std::cout << "Введите любой символ для продолжения: ";
                std::cin >> choice;
                continue;
            }
            if (choice == user1->first)
            {
                std::cout << "Введен собственный логин" << std::endl;
                std::cout << "Введите любой символ для продолжения: ";
                std::cin >> choice;
                continue;
            }
            if (user1->second.checkContact(choice) == true)
            {
                std::cout << "Пользователь с таким логином уже есть в списке контактов" << std::endl;
                std::cout << "Введите любой символ для продолжения: ";
                std::cin >> choice;
                continue;
            }
            Chat newChat;
            Message newMessage(user1->first, "Привет!");
            newChat.addMessage(newMessage);
            chats.push_back(newChat);
            std::list<Chat>::iterator chat = chats.end();
            chat--;
            user1->second.addChat(user2->first, chat);
            user2->second.addChat(user1->first, chat);
        }
        else if (choice == "2")
        {
            user1->second.writeMessage();
        }
        else if (choice == "3")
        {
            user1->second.writeAll();
        }
        else if (choice == "0")
        {
            break;
        }
    }
}

void Server::adminSession()
{
    std::string choice;
    while (true)
    {
        system("clear");
        std::cout << "1 - Список пользователей" << std::endl;
        std::cout << "2 - Прекратить работу чата" << std::endl;
        std::cout << "0 - Завершить сеанс" << std::endl;
        std::cin >> choice;
        if (choice == "1")
        {
            size_t n = 1;
            std::map<std::string, User>::iterator begin = users.begin();
            std::map<std::string, User>::iterator end = users.end(); 
            for (begin; begin != end; begin++)
            {
                std::cout << n << " - " << begin->first << std::endl;
                n++;
            }
            std::cout << "Введите любой символ для продолжения: ";
            std::cin >> choice;
        }
        else if (choice == "2")
        {
            chatWork = false;
            break;
        }
        else if (choice == "0")
        {
            break;
        }
    }
}