#include <iostream>
#include <winsock2.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define PORT 5155
#define BUFLEN 2048

struct Command {
    string action;
    vector<string> parameters;
};

map<string, string> commandDescriptions = {
    {"clear display", "color"},
    {"draw pixel", "x0 y0 color"},
    {"draw line", "x0 y0 x1 y1 color"},
    {"draw rectangle", "x0 y0 w h color"},
    {"fill rectangle", "x0 y0 w h color"},
    {"draw ellipse", "x0 y0 radius_x radius_y color"},
    {"fill ellipse", "x0 y0 radius_x radius_y color"},
    {"draw circle", "x0 y0 radius color"},
    {"fill circle", "x0 y0 radius color"},
    {"draw rounded rectangle", "x0 y0 w h radius color"},
    {"fill rounded rectangle", "x0 y0 w h radius color"},
    {"draw text", "x0 y0 color font_number length text"},
    {"draw image", "x0 y0 w h data"}
};

void executeCommand(const Command& command) {
    cout << "Команда: " << command.action << endl;
    cout << "Параметры: ";
    for (const string& param : command.parameters) {
        cout << param << " ";
    }
    cout << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");

    WSADATA wsData;
    if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
        cerr << "Ошибка инициализации WinSock." << endl;
        return 1;
    }

    SOCKET serverSocket;
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Ошибка создания сокета." << endl;
        return 2;
    }

    sockaddr_in serverAddr, clientAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Ошибка при привязке соксета к порту." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 3;
    }

    cout << "Сервер запущен и ждет команды от клиента..." << endl;

    char buf[BUFLEN];
    int clientAddrLen = sizeof(clientAddr);

    while (true) {
        int bytesReceived = recvfrom(serverSocket, buf, BUFLEN, 0, (sockaddr*)&clientAddr, &clientAddrLen);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Ошибка при получении данных." << endl;
            continue;
        }

        buf[bytesReceived] = '\0';

        Command receivedCommand;
        istringstream commandStream(buf);
        string commandLine;

        while (getline(commandStream, commandLine, '\n')) {
            istringstream iss(commandLine);
            iss >> receivedCommand.action;

            string parameter;
            while (iss >> parameter) {
                receivedCommand.parameters.push_back(parameter);
            }

            executeCommand(receivedCommand);
        }
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
