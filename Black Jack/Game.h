#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class PokerGame {
    vector<vector<string>> players;
    int numPlayers;

    // Отображение рук игроков
    void ShowAllHands(SOCKET clientSocket) const {
        char buffer[1024];
        for (int i = 0; i < numPlayers; ++i) {
            int messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (messageReceived <= 0) {
                cerr << "Error: Failed to receive username" << endl;
                return;
            }
            buffer[messageReceived] = '\0'; // Окончание строки
            cout << "Player " << i + 1 << ": " << buffer << endl;
            memset(buffer, 0, sizeof(buffer));

            // Отображение карт каждого игрока
            for (const auto& card : players[i]) {
                messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
                if (messageReceived <= 0) {
                    cerr << "Error: Failed to receive card" << endl;
                    return;
                }
                buffer[messageReceived] = '\0';
                cout << card << " ";
                memset(buffer, 0, sizeof(buffer));
            }
            cout << endl;
        }
    }

    // Выбор победителя
    void DetermineWinner(SOCKET clientSocket) {
        string bestHandType = "High Card";
        int winnerIndex = 0;
        char buffer[1024];

        // Для каждого игрока можно применить логику для оценки их руки (handEvaluator)
        for (int i = 0; i < numPlayers; ++i) {
            // Здесь нужно использовать объект PokerHand для анализа руки игрока
            // PokerHand handEvaluator(players[i]);
            // string handType = handEvaluator.EvaluateHand();

            // Для демонстрации выводим только информацию о каждой руке
            int messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (messageReceived <= 0) {
                cerr << "Error: Failed to receive hand type" << endl;
                return;
            }
            buffer[messageReceived] = '\0';
            cout << "Player " << i + 1 << " Hand: " << buffer << endl;
            memset(buffer, 0, sizeof(buffer));
        }

        // Ожидание результатов на сервере (например, наибольшая рука)
        int messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (messageReceived <= 0) {
            cerr << "Error: Failed to receive winner" << endl;
            return;
        }
        buffer[messageReceived] = '\0';
        cout << "Winner: " << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
    }

public:
    PokerGame(int playersCount) : numPlayers(playersCount) {
        players.resize(numPlayers);
        srand(static_cast<unsigned>(time(0))); // Для перемешивания карт
    }

    // Запуск игры
    void StartGame(SOCKET clientSocket) {
        while (true) {
            ShowAllHands(clientSocket);
            DetermineWinner(clientSocket);

            char choice;
            int bytesReceived = recv(clientSocket, &choice, 1, 0);
            if (bytesReceived <= 0) {
                cerr << "Client disconnected or error receiving data" << endl;
                closesocket(clientSocket);
                return;
            }

            switch (choice) {
            case 27: // ESC для выхода
                send(clientSocket, "Game Over", 9, 0);
                return;
            default:
                send(clientSocket, "Next Game Starting...", 2, 0);
                break;
            }
        }
    }
};
