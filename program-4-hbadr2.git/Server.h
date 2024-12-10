#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

class Server {
private:
    int serverSocket;
    vector<int> clientsWaiting;
    map<int, string> clientNames;
    mutex clientMutex;
    bool isRunning;

    string getCurrentTimeStamp();

public:
    
    //Constructor
   Server();
   
   ~Server();

    //int getServer();

    //void setServer(int s);

    bool startServer(int port);

    void stopServer();

    //void run();

    void acceptConnections();

    void broadcastMessage(const string& message, int senderSocket);

    //void handleDisconnection(int s);

    void handleClient(int clientSocket);
};

#endif