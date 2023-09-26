#include <iostream>
#include <winsock2.h>
#include <sstream>
#include <string>

using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define SERVER "127.0.0.1"
#define PORT 5155
#define BUFLEN 2048

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");

    WSADATA wsData;
    if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
        cerr << "Ошибка инициализации WinSock." << endl;
        return 1;
    }

    SOCKET clientSocket;
    clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Ошибка создания сокета." << endl;
        return 2;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER);

    char message[BUFLEN];
    while (true) {
        cout << "Введите команду и параметры (например, 'draw pixel 10 20 FF00FF'): ";
        cin.getline(message, BUFLEN);

        if (sendto(clientSocket, message, strlen(message), 0, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            cerr << "Ошибка при отправке данных." << endl;
            continue;
        }
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
