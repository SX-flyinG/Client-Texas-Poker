class UserLobby {
    char buffer[1024];
    char choice;

public:
    int MainMenu(SOCKET clientSocket) {
        while (true) {
            int numPlayers = 1; 
            PokerGame pokerGame(numPlayers);
            memset(buffer, 0, sizeof(buffer));
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                cout << buffer << endl;
            }
            else {
                cerr << "Error: Failed to receive menu from server" << endl;
                return 1;
            }

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
                    return 1;
                }
                break;
            }
            else if (choice == '2') {
                Rules(clientSocket);
            }
            else if (choice == '1') {
                pokerGame.StartGame(clientSocket);
            }
        }
        return 0;
    }

    void Rules(SOCKET clientSocket) {
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

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        send(clientSocket, &choice, sizeof(choice), 0);
        MainMenu(clientSocket);
    }
};