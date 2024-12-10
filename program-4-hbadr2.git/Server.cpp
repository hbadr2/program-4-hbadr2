#include "Server.h"
int s;

Server::Server() {
    s = -1;
}

Server::~Server() {
    //stopServer();
}

int Server::getServer() {
    int s;
    return s;
}

void Server::setServer(int s) {
    server = s;
}

bool Server::startServer(int port) {
    cout << "Server started on port " << port << endl;
    return true;
}

void Server::stopServer() {
    cout << "Server stopped." << endl;
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