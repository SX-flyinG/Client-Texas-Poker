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

	void ShowAllHands(SOCKET clientSocket) const {
		char buffer[1024];
		for (int i = 0; i < numPlayers; ++i) {
			int messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
			if (messageReceived <= 0) {
				cerr << "Error: Failed to receive username" << endl;
				return;
			}
			buffer[messageReceived] = '\0';
			cout << "Player " << i + 1 << ": " << buffer << endl;
			memset(buffer, 0, sizeof(buffer));

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

	void PlayerBets(SOCKET clientSocket) {
		char buffer[1024];
		for (int i = 0; i < numPlayers; ++i) {
			int bet;
			cout << "Enter bet for Player " << i + 1 << ": ";
			cin >> bet;
			send(clientSocket, reinterpret_cast<char*>(bet), sizeof(bet), 0);

			int messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
			if (messageReceived <= 0) {
				cerr << "Error: Failed to receive response" << endl;
				return;
			}
			buffer[messageReceived] = '\0';
			cout << buffer << endl;
			memset(buffer, 0, sizeof(buffer));
		}
	}

	void DetermineWinner(SOCKET clientSocket) {
		char buffer[1024];

		for (int i = 0; i < numPlayers; ++i) {
			int messageReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
			if (messageReceived <= 0) {
				cerr << "Error: Failed to receive hand type" << endl;
				return;
			}
			buffer[messageReceived] = '\0';
			cout << "Player " << i + 1 << " Hand: " << buffer << endl;
			memset(buffer, 0, sizeof(buffer));
		}

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
	PokerGame() : numPlayers(0) {}



	void StartGame(SOCKET clientSocket) {
		ShowAllHands(clientSocket);
		PlayerBets(clientSocket);
		DetermineWinner(clientSocket);
	}
};
