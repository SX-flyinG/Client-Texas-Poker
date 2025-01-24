#include "Game.h"

class UserLobby {
    char buffer[1024];
    char choice;

public:
    int MainMenu(SOCKET clientSocket) {
            int numPlayers = 1;
            PokerGame poker;
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                cout << buffer << endl;
            }
            else {
                cerr << "Error: Failed to receive menu from server" << endl;
                return 0;
            }
            memset(buffer, 0, sizeof(buffer));
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            send(clientSocket, &choice, sizeof(choice), 0);

            if (choice == '0' || choice == '3') {
                memset(buffer, 0, sizeof(buffer));
                int message = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
                if (message > 0) {
                    buffer[message] = '\0';
                    cout << buffer << endl;
                }
                else {
                    cerr << "Error: Failed to receive exit message from server" << endl;
                    return 0;
                }
                return 0;
            }
            else if (choice == '2') {
                Rules(clientSocket);
            }
            else if (choice == '1') {
                poker.StartGame(clientSocket);
            }
    }

    void Rules(SOCKET clientSocket) {
        system("cls");
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            cout << buffer << endl;
        }
        else {
            cerr << "Error: Failed to receive rules menu from server" << endl;
            return;
        }

        cin >> choice;
        cin.ignore();

        send(clientSocket, &choice, sizeof(choice), 0);
    }
};