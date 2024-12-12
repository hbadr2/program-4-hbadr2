#include "Client.h"

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
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp.s_str());

    if (connect (clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Error connecting to server" << endl;
        return false;
    }

    send(clientSocket, name.c_str(), name.size(), 0);

    thread(&Client::receiveMessages, this).detach();
    cout << "Connected to server!" << endl;
    return true;
}


//////
cout << "Connected to server!" << endl;
thread(&Client::receiveMessages, this).detach();
return true;

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
