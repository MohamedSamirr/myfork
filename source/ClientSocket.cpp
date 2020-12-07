#include <string>
#include "../headers/ClientSocket.h"

ClientSocket::ClientSocket() : UDPSocket() {
    UDPSocket::initializeClientSocket();
}

bool ClientSocket::initializeClient(std::string _peerAddr, int _peerPort) {
    UDPSocket::initializeClientPeer(&_peerAddr[0], _peerPort);
    return true;
}

bool ClientSocket::initializeBroadcastClient(std::string _peerAddr, int _peerPort) {
    return UDPSocket::initializeBroadcastClient(&_peerAddr[0], _peerPort);
}

ClientSocket::~ClientSocket() {

}
