#include "Server.h"
#include <iostream>

using namespace std;

int s;

Server::Server() {
    s = -1;
}

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
    cout << "Server started on port " << port << endl;
    s = 1;
    return true;
}

void Server::stopServer() {
    if (s == 1) {
        cout << "Server stopped." << endl;
        s = -1;
    } else {
        cout << "Server is already stopped." << endl;
    }
}

void Server::run() {
    cout << "Server is running ..." << endl;
}

void Server::acceptConnections() {
    //something
}

void Server::broadcastMessage(const string& message, int s) {
    //something
}

void Server::handleDisconnection(int s) {
    //something
}