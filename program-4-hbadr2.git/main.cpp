#include "Server.h"
#include "Client.h"
#include <iostream>
#include <string>

using namespace std;

void displayMainMenu() {
    cout << "\nWelcome to the client-server chat application!" << endl;
    cout << "\n1. Connect to the Server" << endl;
    cout << "2. Send a message" << endl;
    cout << "3. Exit" << endl;
    cout << "\nChoose an option (enter either 1, 2, or 3): "<< endl;
}

int  main() {
    cout << "\nThe chat room is currently open ..." << endl;

    Server server;

    thread serverThread([&server]() { acceptConnections(); });

    if (!server.startServer(80)) {
        return -1;
    }

    Client client1;
    Client client2;

    

    server.startServer(80);

    string choice;
    bool isRunning = true;
    string name;
    string message;

    while (isRunning) {
        displayMainMenu();
        cin >> choice;

        if (choice == "1") {
            
            //connect client to the server
            cout << "\nEnter your name: ";
            cin >> name;
            client.setName(name);
            client.connectToServer("128.0.0.1", 80);
            cout << "You are now connected as " << name << "." << endl;
        
        } else if (choice == "2") {
            
            //send a message
            cout << "\nEnter your message: ";
            cin.ignore();
            getline(cin, message);
            client.sendMessage(message);
            server.broadcastMessage(name + ": " + message, 0);
        
        } else if (choice == "3") {

            //exit program
            cout << "\nThank you for using the chat room!" << endl;
            isRunning = false;
        
        } else {
            cout << "Please try again and enter a valid choice. " << endl;
        }
    }
    //server.stopServer();
    return 0;

    /*
    client.connectToServer("127.0.0.1", 80);

    client.setName("John Smith");
    client.sendMessage("Hello, everyone :)");

    server.broadcastMessage("John Smith: Hello everyone :) ", 0);

    return 0;
    */
}
