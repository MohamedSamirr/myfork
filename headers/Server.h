#ifndef MYFORK_SERVER_H
#define MYFORK_SERVER_H

#include "ServerSocket.h"
#include "Message.h"
#include "MessageStructure.h"
#include "myfork.h"

class Server {
private:
    ServerSocket *udpServerSocket;
    std::string hostname;
    int port;
    MyFork forking;

protected:
    Message *getRequest();

public:
    void sendReply(Message *_message);

    Server();

    Server(const std::string &_listen_hostname, int _listen_port);

    bool initBroadcast(int _broadcastPort);

    bool send(Message *_message);

    Message *listenToBroadcasts();

    Message *receive();

    Message::RPC_ID *constructRPC();

    template<typename T>
    Message *
    saveAndGetMessage(const T &messageStructure, Message::MessageType messageType, Message::OperationType operation) {
        std::string serialized = save<T>(messageStructure);
        return new Message(messageType, operation, serialized, serialized.length(), *(this->constructRPC()));
    }

    void serveRequest();

    ~Server();
};

#endif //MYFORK_SERVER_H
