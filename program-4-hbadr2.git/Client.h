#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>

//using System;
//namespace program_4_hbadr2.git
using namespace std;

class Client {

private:

	int awaitingClient;
	string name;

	//void receiveMessage();
	//void handleServerDisconnection();

public:

	//constructor
	Client();

	//getters and setters
	int getAwaitingClient();

	void setAwaitingClient();

	string getName();

	void setName(string& name);

	//connecting and disconnecting to/from the server
	boolean connectToServer (const string& serverAddress, int port);

	void disconnect();

	//sending/receiving messages
	void sendMessage(const string& message);

	void receiveMessages();
}

#endif