#include <cstring>
#include <iostream>
#include "../headers/Message.h"
#include "../headers/Server.h"

/**
 * Constructors
 */

Server::Server() {
    this->udpServerSocket = new ServerSocket();
    this->forking = MyFork();
}

Server::Server(const std::string &_listen_hostname, int _listen_port) {
    this->udpServerSocket = new ServerSocket();
    this->udpServerSocket->initializeServer(_listen_hostname, _listen_port);
    this->hostname = _listen_hostname;
    this->port = _listen_port;
    this->forking = MyFork();
}

/*************************************************************************************/

bool Server::initBroadcast(int _broadcastPort) {
    return this->udpServerSocket->initializeBroadcastServer(_broadcastPort);
}

void Server::sendReply(Message *_message) {
    std::string serialized = _message->serialize();
    this->udpServerSocket->writeToSocket(&serialized[0], serialized.length());
}

Message *Server::getRequest() {
    char *message = static_cast<char *>(malloc(MAX_MESSAGE_SIZE));
    this->udpServerSocket->readFromSocketWithBlock(message, MAX_MESSAGE_SIZE);
    return new Message(message);  //in new thread
}

void Server::serveRequest() {
    Message *msg = receive();
    std::cout << "Server Message Received: " << msg->getMessage() << std::endl;
    if (msg->getMessage() == "fork") {
        std::cout << "Remote forking message...\nForking Child Process" << std::endl;
        std::string cpid = "Remote Child pid = " + std::to_string(this->forking.executeMyForkServer());
        Message::RPC_ID rpc = Message::RPC_ID();
        send(new Message(Message::MessageType::Request, Message::OperationType::ECHO, cpid,
                         cpid.length(), rpc));
        std::cout << "I AM THE CHILD!";
    } else if (msg->getMessage() == "q") {
        std::cout << "Server found exit message...\nTerminating Process" << std::endl;
        exit(EXIT_SUCCESS);
    } else {
        send(msg);
    }
}

bool Server::send(Message *_message) {
    std::string serialized = _message->serialize();
    this->udpServerSocket->writeToSocket(&serialized[0], serialized.length());
    return true;
}

Message *Server::listenToBroadcasts() {
    char *broadcast = static_cast<char *>(malloc(MAX_READ_MESSAGE_SIZE));
    this->udpServerSocket->readSocketBroadcast(broadcast, MAX_READ_MESSAGE_SIZE);
    return new Message(broadcast);
}

Message *Server::receive() {
    char *reply = static_cast<char *>(malloc(MAX_READ_MESSAGE_SIZE));
    this->udpServerSocket->readFromSocketWithBlock(reply, MAX_READ_MESSAGE_SIZE);
    return new Message(reply);
}


Message::RPC_ID *Server::constructRPC() {
    return new Message::RPC_ID(this->hostname, this->port);
}

/*************************************************************************************/
/**
 * Destructors
 */

Server::~Server() {

}

/*************************************************************************************/