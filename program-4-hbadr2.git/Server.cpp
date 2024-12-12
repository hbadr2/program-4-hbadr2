#include "Server.h"
#include <iostream>

using namespace std;

int s;

Server::Server() : serverSocket(-1), isRunning(false) {}

Server::~Server() {
    stopServer();
}

int Server::getServer() {
    int s;
    return s;
}

void Server::setServer(int serverState) {
    s = serverState;
}

bool Server::startServer(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cout << "Error creating socket" << endl;
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Error binding socket" << endl;
        return false;
    }

    if (listen(serverSocket, 10) < 0) {
        cout << "Error listening on socket." << endl;
        return false;
    }

    isRunning = true;
    cout << "Server started on port " << port << endl;
    return true;
}

void Server::stopServer() {
    isRunning = false;
    close(serverSocket);
    cout << "Server stopped." << endl;
}

void Server::run() {
    cout << "Server is running ..." << endl;
}

void Server::acceptConnections() {
    while (isRunning) {
        sockaddr_in clientAddr;
        socklen_t clientLen =  sizeof(clientAddr);
        int clientSocket =  accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            cout << "Error accepting connection" << endl;
            continue;
        }

        {
            lock_guard<mutex> lock(clientMutex);
            clients.push_back(clientSocket);
        }
        thread(&Server::handleClient, this, clientSocket).detach();
        cout << "A new client has joined!" << endl;
    }
}

void Server::broadcastMessage(const string& message, int senderSocket) {
    lock_guard<mutex> lock(clientMutex);
    for (int clientSocket : clients) {
        if (clientSocket != senderSocket) {
            send(clientSocket, message.c_str(), message.size(), 0);
        }
    }
}

void Server::handleDisconnection(int s) {
    //something
}

void Server::handleClient(int clientSocket) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    recv(clientSocket, buffer, sizeof(buffer), 0);
    string clientName(buffer);

    {
        lock_guard<mutex> lock(clientMutex);
        clientNames[clientSocket] = name;;
    }

    broadcastMessage(name + " has joined the chat!", clientSocket);

    while (isRunning) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            cout << clientName << "disconnected." << endl;
            close(clientSocket);

            {
                lock_guard<mutex> lock(clientMutex);
                clients.erase(remove(clients.begin(), clients.end(), clientSocket), clients.end());
                clientNames.erase(clientSocket);
            }
            broadcastMessage(clientName + " has left the chat.", clientSocket);
            break;
        }
        string message(buffer);
        if (message == "exit") {
            broadcastMessage(clientName + " has left the chat", clientSocket);
            close(clientSocket);

            {
                lock_guard<mutex> lock(clientMutex);
                clients.erase(remove(clients.begin(), clients.end(), clientSocket), clients.end());
                clientNames.erase(clientSocket);
            }
            break;
        }
        string timeStampedMessage = getCurrentTimeStamp() + message;
        cout << timeStampedMessage << endl;
        broadcastMessage(timeStampedMessage, clientSocket);
    }
}

string Server::gteCurrentTimeStamp() {
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtm);
    return string(buffer);
}