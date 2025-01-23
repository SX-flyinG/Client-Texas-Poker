#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <conio.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

#include "Registration.h" 
#include "Lobby.h"
#include "Game.h"

int main() {
    const string SERVER_IP = "127.0.0.1";
    const int SERVER_PORT = 55805;
    Registration registration;
    UserLobby userLobby;


    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Failed to initialize Winsock" << endl;
        return 1;
    }

    // Ñîçäàíèå ñîêåòà
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Error: Failed to create socket" << endl;
        WSACleanup();
        return 1;
    }

    // Íàñòðîéêà àäðåñà ñåðâåðà
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP.c_str(), &serverAddr.sin_addr);

    // Ïîäêëþ÷åíèå ê ñåðâåðó
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Error: Failed to connect to the server" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server " << SERVER_IP << ":" << SERVER_PORT << endl;

    registration.reg(clientSocket);
    while (true) {
        if (userLobby.MainMenu(clientSocket) == 0) {
            // Запуск игры
            int numPlayers = 1; // Предположим, 1 игрок для простоты
            PokerGame pokerGame(numPlayers);
            pokerGame.StartGame(clientSocket);

            // Предложить продолжить игру или выйти
            char choice;
            cout << "Do you want to play again? (y/n): ";
            cin >> choice;
            if (choice == 'n') {
                break; // Выход из игры
            }
        }
    }

    // Çàâåðøåíèå ðàáîòû êëèåíòà
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
