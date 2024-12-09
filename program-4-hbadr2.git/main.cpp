#include "Server.h"
#include "Client.h"
#include <iostream>

using namespace std;

int  main() {
    cout << "Thank you for contacting us! Someone will be with you shortly!" << endl;

    Server server;
    Client client;

    server.startServer(8080);
    client.connectToServer("127.0.0.1", 8080);

    client.setUsername("John Smith");
    client.sendMessage("Hello, everyone :)");

    server.broadcastMessage("John Smith: ", 0j;

    return 0;
}
