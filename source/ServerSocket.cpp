#include "../headers/ServerSocket.h"

ServerSocket::ServerSocket() : UDPSocket() {

}

bool ServerSocket::initializeServer(std::string _myAddr, int _myPort) {
    return UDPSocket::initializeServer(&_myAddr[0], _myPort);
}

bool ServerSocket::initializeBroadCastServer(int _broadcastPort) {
    return UDPSocket::initializeBroadcastServer(_broadcastPort);
}

ServerSocket::~ServerSocket() {

}
