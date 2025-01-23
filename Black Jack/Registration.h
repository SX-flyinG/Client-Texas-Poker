class Registration {
    string username;
    string password;
    int age = 0;
    int choice = -1;

public:
    void reg(SOCKET clientSocket);
    void registration(SOCKET clientSocket);
    void logIn(SOCKET clientSocket);
};

/* �������� �������������� ������� � �������� */
void Registration::reg(SOCKET clientSocket) {
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        cout << buffer << endl;  // ����������� ����, ����������� �� �������
    }
    else {
        cerr << "Error: Failed to receive menu from server" << endl;
        return;
    }

    // ��������� ������ ������������
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    
    while (choice < 0 || choice  > 2) {
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
    }

    // �������� ������ �� ������
    string choiceStr = to_string(choice);
    send(clientSocket, choiceStr.c_str(), choiceStr.size(), 0);

    if (choice == 1) {
        registration(clientSocket);
    }
    else if (choice == 2) {
        logIn(clientSocket);
    }
    else {
        cout << "Exiting program." << endl;
    }
}

/* ����������� ������������ */
void Registration::registration(SOCKET clientSocket) {
    char userReg[1024];
    int userBytesReceived = recv(clientSocket, userReg, sizeof(userReg) - 1, 0);
    if (userBytesReceived > 0) {
        userReg[userBytesReceived] = '\0';
        cout << userReg << endl;  // ����������� ������ �� �������
    }
    else {
        cerr << "Error: Failed to receive response from server" << endl;
    }
    // ���� ����� ������������
    getline(cin, username);
    send(clientSocket, username.c_str(), username.size(), 0);

    // ���� ���� ��������
    char ageReg[1024];
    int ageBytesReceived = recv(clientSocket, ageReg, sizeof(ageReg) - 1, 0);
    if (ageBytesReceived > 0) {
        ageReg[ageBytesReceived] = '\0';
        cout << ageReg << endl;  // ����������� ������ �� �������
    }
    else {
        cerr << "Error: Failed to receive response from server" << endl;
    }
    cin >> age;
    cin.ignore();
    string ageStr = to_string(age);
    send(clientSocket, ageStr.c_str(), ageStr.size(), 0);

    // ���� ������
    char passReg[1024];
    int passBytesReceived = recv(clientSocket, passReg, sizeof(passReg) - 1, 0);
    if (passBytesReceived > 0) {
        passReg[passBytesReceived] = '\0';
        cout << passReg << endl;  // ����������� ������ �� �������
    }
    else {
        cerr << "Error: Failed to receive response from server" << endl;
    }
    getline(cin, password);
    send(clientSocket, password.c_str(), password.size(), 0);

    // �������� ������������� �� �������
 
}

/* ���� � ������� */
void Registration::logIn(SOCKET clientSocket) {
    char userLogIn[1024];
    int userBytesReceived = recv(clientSocket, userLogIn, sizeof(userLogIn) - 1, 0);
    if (userBytesReceived > 0) {
        userLogIn[userBytesReceived] = '\0';
        cout << userLogIn << endl;  // ����������� ������ �� �������
    }
    else {
        cerr << "Error: Failed to receive response from server" << endl;
    }
    // ���� ����� ������������
    getline(cin, username);
    send(clientSocket, username.c_str(), username.size(), 0);

    char passlogIn[1024];
    int passBytesReceived = recv(clientSocket, passlogIn, sizeof(passlogIn) - 1, 0);
    if (passBytesReceived > 0) {
        passlogIn[passBytesReceived] = '\0';
        cout << passlogIn << endl;  // ����������� ������ �� �������
    }
    else {
        cerr << "Error: Failed to receive response from server" << endl;
    }
    // ���� ������
    getline(cin, password);
    send(clientSocket, password.c_str(), password.size(), 0);

    char logInSuccessfully[1024];
    int sucessBytesReceived = recv(clientSocket, logInSuccessfully, sizeof(logInSuccessfully) - 1, 0);
    if (sucessBytesReceived > 0) {
        logInSuccessfully[sucessBytesReceived] = '\0';
        cout << logInSuccessfully << endl;  // ����������� ������ �� �������
    }
    else {
        cerr << "Error: Failed to receive response from server" << endl;
    }

}
