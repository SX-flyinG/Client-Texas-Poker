class UserLobby {
    char buffer[1024]; // Buffer for server messages

public:

    void MainMenu(SOCKET clientSocket) {
        while (true) {
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                cout << buffer << endl;  // Отображение меню, полученного от сервера
            }
            else {
                cerr << "Error: Failed to receive menu from server" << endl;
                return;
            }
        }
    }
};
