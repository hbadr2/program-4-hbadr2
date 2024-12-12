#include "Client.h"
#include <iostream>
#include <cstring>

using namespace std;

Client::Client() {
    clientSocket = -1;
}

Client::~Client() {
    if (clientSocket >= 0) {
        close(clientSocket);
    }
}

int Client::getAwaitingClient() const {
    return awaitingClient;
}

void Client::setAwaitingClient(int num) {
    awaitingClient = num;
}

string Client::getName() const {
    return name;
}

void Client::setName(const string& username){
    name = username;
}

bool Client::connectToServer(const string& serverIp, int port) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0){
        cout << "Error creating socket" << endl;
        return false;
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr) <= 0) {
        cout << "Invalid server IP address" << endl;
        return false;
    }

    if (connect (clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Error connecting to server" << endl;
        return false;
    }

    send(clientSocket, name.c_str(), name.size(), 0);

    thread t(&Client::receiveMessages, this);
    t.detach();
    cout << "Connected to server!" << endl;
    return true;
}

void Client::sendMessage(const string& message) {
    send(clientSocket, message.c_str(), message.size(), 0);
}

void Client::receiveMessages() {
    char buffer [1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cout << "Disconnected from server." <<endl;
            break;
        }
        cout << buffer << endl;
    }
}
