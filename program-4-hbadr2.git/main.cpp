#include "Server.h"
#include "Client.h"
#include <iostream>
#include <string>

using namespace std;

int  main() {
    cout << "Thank you for contacting us! Someone will be with you shortly!" << endl;

    Server server;
    Client client;

    server.startServer(8080);
    client.connectToServer("127.0.0.1", 8080);

    client.setName("John Smith");
    client.sendMessage("Hello, everyone :)");

    server.broadcastMessage("John Smith: Hello everyone :) ", 0);

    return 0;
}
