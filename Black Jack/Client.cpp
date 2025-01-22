#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <conio.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

#include "Registration.h" 
#include "Lobby.h"

int main() {
    const string SERVER_IP = "127.0.0.1";
    const int SERVER_PORT = 55805;
    Registration registration;
    UserLobby userLobby;

    // ������������� Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Failed to initialize Winsock" << endl;
        return 1;
    }

    // �������� ������
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Error: Failed to create socket" << endl;
        WSACleanup();
        return 1;
    }

    // ��������� ������ �������
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP.c_str(), &serverAddr.sin_addr);

    // ����������� � �������
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Error: Failed to connect to the server" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server " << SERVER_IP << ":" << SERVER_PORT << endl;

    // �������������� � ��������
    registration.reg(clientSocket);
    userLobby.MainMenu(clientSocket);

    // ���������� ������ �������
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
