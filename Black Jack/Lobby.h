// Базовый абстрактный класс
class IMenu {
public:
    virtual int MainMenu(SOCKET clientSocket) = 0;
    virtual void Rules(SOCKET clientSocket) = 0;
    virtual ~IMenu() = default; // Виртуальный деструктор для безопасности
};

// Класс UserLobby реализует интерфейс IMenu
class UserLobby : public IMenu {
    char buffer[1024];
    char choice;

public:
    int MainMenu(SOCKET clientSocket) override {
        while (true) {
            memset(buffer, 0, sizeof(buffer)); 
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0'; 
                cout << buffer << endl;
            } else {
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
                } else {
                    cerr << "Error: Failed to receive exit message from server" << endl;
                    return 1;
                }
                break;
            } else if (choice == '2') {
                Rules(clientSocket); 
            }
        }
        return 0;
    }

    void Rules(SOCKET clientSocket) override {
        memset(buffer, 0, sizeof(buffer)); 
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            cout << buffer << endl;
        } else {
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