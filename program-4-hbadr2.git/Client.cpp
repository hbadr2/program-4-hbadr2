#include "Client.h"

Client::Client() {
    awaitingClient = -1;
}

Client::getAwaitingClient() {
    return awaitingClient;
}

Client::setAwaitingClient(int num) {
    awaitingClient = num;
}

void Client::getName() {
    return name;
}

void Client::setName(string& name){
    this->name = name;
}

bool Client::connecttoServer(string& serverAddress, int port) {
    cout << "Connecting to server ..." << endl;
}

void Client::sendMessage(string& message) {
    cout << "Your message: " << message << "was sent successfully!" << endl;
}

void Client::receiveMessages() {
    cout << "Receiving messsages..." << endl;
}
