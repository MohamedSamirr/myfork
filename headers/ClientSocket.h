#ifndef MYFORK_CLIENTSOCKET_H
#define MYFORK_CLIENTSOCKET_H

#include "UDPSocket.h"
#include <string>

class ClientSocket : public UDPSocket {
public:
    ClientSocket();

    bool initializeClient(std::string _peerAddr, int _peerPort);

    bool initializeBroadcastClient(std::string _peerAddr, int _peerPort);

    ~ClientSocket();
};

#endif //MYFORK_CLIENTSOCKET_H
