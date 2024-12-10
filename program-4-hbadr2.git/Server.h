#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;

class Server {
private:
    int server;
    vector<int> clientsAwaiting;
    map <int, string> clientNames;

public:
    
    //Constructor
   Server();
   
   ~Server();

    int getServer();

    void setServer(int s);

    bool startServer(int port);

    void stopServer();

    void run();

    void acceptConnections();

    void broadcastMessage(const string& message, int s);

    void handleDisconnection(int s);
}
;

#endif