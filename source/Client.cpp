#include <iostream>
#include "../headers/Client.h"

/**
 * Constructors
 */

Client::Client() {
    this->udpSocket = new ClientSocket();
    this->forking = MyFork();
}

Client::Client(std::string _hostname, int _port) {
    this->udpSocket = new ClientSocket();
    this->udpSocket->initializeClient(_hostname, _port);
    this->forking = MyFork();
}

/*************************************************************************************/

bool Client::connectToServer(const std::string &_hostname, int _port) {
    return this->udpSocket->initializeClient(_hostname, _port);
}

bool Client::initBroadcast(std::string _broadcastAddress, int _broadcastPort) {
    return this->udpSocket->initializeBroadcastClient(_broadcastAddress, _broadcastPort);
}

Message *Client::execute(Message *_message) {
    if(_message->getMessage() == "fork") {
        this->forking.executeMyForkClient();
    }
    send(_message);
    return receiveWithBlock();
}

bool Client::send(Message *_message) {
    std::string serialized = _message->serialize();
    this->udpSocket->writeToSocket(&serialized[0], serialized.length());
    return true;
}

Message::RPC_ID *Client::constructRPC() {
    return new Message::RPC_ID(this->udpSocket->getFilterAddress(), this->udpSocket->getMyPort());
}

bool Client::broadcast(Message *_message) {
    std::string serialized = _message->serialize();
    this->udpSocket->writeBroadcastToSocket(&serialized[0], serialized.length());
    return true;
}

Message *Client::receiveWithBlock() {
    char *reply = static_cast<char *>(malloc(MAX_READ_MESSAGE_SIZE));
    this->udpSocket->readFromSocketWithBlock(reply, MAX_READ_MESSAGE_SIZE);
    return new Message(reply);
}

/*************************************************************************************/
/**
 * Destructors
 */

Client::~Client() {
}

/*************************************************************************************/