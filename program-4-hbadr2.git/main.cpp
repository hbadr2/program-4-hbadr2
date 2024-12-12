#include "Server.h"
#include "Client.h"
#include <iostream>
#include <string>
#include <thread>

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

    if (!server.startServer(80)) {
        cerr << "Failed to start the server. Exiting ..." << endl;
        return -1;
    }

    thread serverThread(&Server::acceptConnections, &server);

    Client client;
    string name, choice, message;
    bool isRunning = true;

    server.startServer(80);
/*
    string choice;
    bool isRunning = true;
    string name;
    string message;
*/
    while (isRunning) {
        displayMainMenu();
        cin >> choice;

        if (choice == "1") {
            
            //connect client to the server
            cout << "\nEnter your name: ";
            cin >> name;
            client.setName(name);
            if (client.connectToServer("128.0.0.1", 80)) {
                 cout << "You are now connected as " << name << "." << endl;
            } else {
                cout << "Failed to connect to the server. Please try again." << endl;
            }
        
        } else if (choice == "2") {
            //send a message
            if (name.empty()){
                cout << "You must connect to the server first!" << endl;
                continue;
            }
            cout << "\nEnter your message: ";
            cin.ignore();
            getline(cin, message);
            client.sendMessage(message);
        
        } else if (choice == "3") {

            //exit program
            cout << "\nThank you for using the chat room!" << endl;
            isRunning = false;
        
        } else {
            cout << "Please try again and enter a valid choice. " << endl;
        }
    }
    
    server.stopServer();
    if (serverThread.joinable()) {
        serverThread.join();
    }
    return 0;
}
