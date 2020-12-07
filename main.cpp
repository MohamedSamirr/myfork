#include <iostream>
#include <cstring>
#include "headers/Server.h"
#include "headers/Client.h"
#include "headers/Message.h"

int main() {
    pid_t pid = fork();

    if(pid < 0)
        throw "Cannot create child process";

    if(pid == 0) {
        std::string listenHostname = "127.0.0.1";
        int listenPort = 3000;
        Server s = Server(listenHostname, listenPort);
        std::cout << "Listening for requests from clients...\n";
        while (1) {
            s.serveRequest();
        }
    } else if(pid > 0) {
        std::string serverHostname = "127.0.0.1";
        int serverPort = 3000;
        sleep(2);
        Client c = Client(serverHostname, serverPort);
        while (1) {
            char *message = static_cast<char *>(malloc(10000000));
            do {
                std::cout << "Input the message to be sent to the destination server:\n";
                std::cin.getline(message, 10000000, '\n');
            } while (strncmp(message, "", 1) == 0);
            //strcpy(message, "flood");
            Message::RPC_ID rpc = Message::RPC_ID();
            Message msg = Message(Message::MessageType::Request, Message::OperationType::ECHO, message,
                                  strlen(message), rpc);
            Message *reply = c.execute(&msg);
            std::cout << "Reply From Server: " << reply->getMessage() << std::endl;
            if (strncmp(message, "q", 1) == 0)
                break;
        }
    }
}
