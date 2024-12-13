#include "Server.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

/*
int serverSocket;
struct sockaddr_in serverAddr;
*/
Server::Server() {
    serverSocket = -1;
    //serverState = 0;
    isRunning = false;
}

Server::~Server() {
    stopServer();
}

/*
int Server::getServer() {
    int s;
    return s;
}
*/
void Server::setServer(int serverState) {
    this->serverState = serverState;
}

void Server::stopServer() {
    isRunning = false;
    if (serverSocket >= 0) {
        close(serverSocket);
        serverSocket = -1;
    }
    cout << getCurrentTimeStamp() << "Server stopped." << endl;
}

void Server::run() {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    serverSocket =  socket(AF_INET, SOCK_STREAM, 0);
    if  (serverSocket < 0) {
        cout << "Error binding socket." << endl;
        exit(1);
    }
    
    int bindResult =  bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bindResult < 0){
        cout << "Error binding socket." << endl;
        exit(1);
    }

    listen(serverSocket, 5);
    cout << "Server is running ..." << endl;
}

bool Server::startServer(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cout << "Error creating socket" << endl;
        return false;
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
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
    cout <<  getCurrentTimeStamp() << " Server started on port " << port << endl;
    
    thread acceptThread(&Server::acceptConnections, this);
    //thread clientThread([this, clientSocket]() { this->handleClient(clientSocket); });
    acceptThread.detach();

    return true;
}

void Server::acceptConnections() {
    while (isRunning) {
        sockaddr_in clientAddr;
        socklen_t clientLen =  sizeof(clientAddr);
        int clientSocket =  accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
        
        if (clientSocket < 0) {
            if (isRunning) {
                cout << "Error accepting connection" << endl;
            }
            continue;
        }

        {
            lock_guard<mutex> lock(clientMutex);
            clientsWaiting.push_back(clientSocket);
        }
        
        cout << getCurrentTimeStamp() << " Client connected: " << clientSocket << endl;
        
        thread clientThread(&Server::handleClient, this, clientSocket);
        clientThread.detach();
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

void Server::handleClient(int clientSocket) {
    char buffer[1024];
    string clientName;

    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        clientName = string(buffer, bytesReceived);
        {
            lock_guard<mutex> lock(clientMutex);
            clientNames[clientSocket] = clientName;
            clients.push_back(clientSocket);
        }

        cout << getCurrentTimeStamp() << " Client registered: " << clientName << endl;
    } else {
        close(clientSocket);
        return;
    }
    
    while (isRunning) {
        memset(buffer, 0, sizeof(buffer));
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        
        if (bytesReceived <= 0) {
            cout << getCurrentTimeStamp() << " Client disconnected." << clientName << endl;
            {
                lock_guard<mutex> lock(clientMutex);
                clients.erase(remove(clients.begin(), clients.end(), clientSocket), clients.end());
                clientNames.erase(clientSocket);
            }
            close(clientSocket);
            break;
        }
        
        string message =  clientName + ": " + string(buffer, bytesReceived);
        cout << message << endl;
        broadcastMessage(message, clientSocket);
    }
}

string Server::getCurrentTimeStamp() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[8080];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return string(buffer);
}