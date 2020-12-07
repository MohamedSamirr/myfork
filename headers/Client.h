#ifndef MYFORK_CLIENT_H
#define MYFORK_CLIENT_H

#include "ClientSocket.h"
#include "Message.h"
#include "MessageStructure.h"
#include "myfork.h"

class Client {
private:
    ClientSocket *udpSocket;
    MyFork forking;

public:
    Client();

    Client(std::string _hostname, int _port);

    bool connectToServer(const std::string &_hostname, int _port);

    bool initBroadcast(std::string _broadcastAddress, int _broadcastPort);

    Message::RPC_ID *constructRPC();

    Message *execute(Message *_message);

    bool send(Message *_message);

    bool broadcast(Message *_message);

    Message *receiveWithBlock();

    template<typename T>
    Message *
    saveAndGetMessage(const T &messageStructure, Message::MessageType messageType, Message::OperationType operation) {
        std::string serialized = save<T>(messageStructure);
        return new Message(messageType, operation, serialized, serialized.length(), *this->constructRPC());
    }

    ~Client();
};

#endif //MYFORK_CLIENT_H
