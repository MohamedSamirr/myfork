#ifndef MYFORK_SERVERSOCKET_H
#define MYFORK_SERVERSOCKET_H

#include <string>
#include "UDPSocket.h"

class ServerSocket : public UDPSocket {
public:
    ServerSocket();

    bool initializeServer(std::string _myAddr, int _myPort);

    bool initializeBroadCastServer(int _broadcastPort);

    ~ServerSocket();
};

#endif //MYFORK_SERVERSOCKET_H
