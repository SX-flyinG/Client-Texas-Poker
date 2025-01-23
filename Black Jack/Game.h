class PokerGame {
    char buffer[1024];

    // Отображение рук игроков
    void ShowAllHands(SOCKET clientSocket) const {
        for (int i = 0; i < numPlayers; ++i) {
            int messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) {
                cerr << "Error: Failed to receive username" << endl;
                return -1;
            }
            cout <<  buffer;  
            memset(buffer, 0, sizeof(buffer));
            for (const auto& card : players[i]) {
                messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
                if (bytesReceived <= 0) {
                    cerr << "Error: Failed to receive username" << endl;
                    return -1;
                }
                cout <<  buffer;  
                memset(buffer, 0, sizeof(buffer));
            }
            messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) {
                cerr << "Error: Failed to receive username" << endl;
                return -1;
            }
            cout <<  buffer;  
            memset(buffer, 0, sizeof(buffer));
        }
    }

    // Выбор победителя
    void DetermineWinner(SOCKET clientSocket) {
        string bestHandType = "High Card";
        int winnerIndex = 0;

        for (int i = 0; i < numPlayers; ++i) {
            PokerHand handEvaluator(players[i]);
            string handType = handEvaluator.EvaluateHand();
            int messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived <= 0) {
                cerr << "Error: Failed to receive username" << endl;
                return -1;
            }
            cout <<  buffer;  
            memset(buffer, 0, sizeof(buffer));
        }

        messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
                cerr << "Error: Failed to receive username" << endl;
                return -1;
            }
        cout <<  buffer;  
        memset(buffer, 0, sizeof(buffer));
    }


public:
    PokerGame(int playersCount) : numPlayers(playersCount) {
        players.resize(numPlayers);
        srand(static_cast<unsigned>(time(0))); // Для перемешивания
    }

    // Запуск игры
    void StartGame(SOCKET clientSocket) {
        while(true){
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
                case 27:
                    return -1;
                default:
                    send(clientSocket, "Next Game Starting...", 23 , 0);
                    break; 
            }
        }
    }
};
