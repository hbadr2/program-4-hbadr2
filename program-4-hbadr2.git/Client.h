#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <thread>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

class Client {
private:
	int clientSocket;
	string name;

	void receiveMessages();

public:
	//constructor
	Client();
	~Client();

	//getters and setters
	//int getAwaitingClient() const;

	//void setAwaitingClient(int num);

	//string getName() const;

	void setName(const string& name);

	//connecting and disconnecting to/from the server
	bool connectToServer (const string& serverAddress, int port);

	//void disconnect();

	//sending/receiving messages
	void sendMessage(const string& message);

	//void receiveMessages();
};

#endif