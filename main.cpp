#include <locale>
#include "ServerV2.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    system("clear");
    Server server;
    system("clear");
    server.work();
    return 0;
}