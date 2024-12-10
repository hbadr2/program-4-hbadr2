#include "Client.h"

Client::~Client() {
    //empty destructor
}

Client::Client() {
    awaitingClient = -1;
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

void Client::setName(const string& name){
    this->name = name;
}

bool Client::connectToServer(const string& serverAddress, int port) {
    cout << "Connecting to server at " << serverAddress << " on port " << port << endl;
    return true;
}

void Client::sendMessage(const string& message) {
    cout << "Your message: " << message << "was sent successfully!" << endl;
}

void Client::receiveMessages() {
    cout << "Receiving messsages..." << endl;
}
