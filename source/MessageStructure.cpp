#include "../headers/MessageStructure.h"

using namespace MessageStructures;
using namespace MessageStructures::Control;

realSockAddr::realSockAddr() {

}

realSockAddr::realSockAddr(const realSockAddr &other) {
    memcpy(sa_data, other.sa_data, sizeof(other.sa_data));
    sa_family = other.sa_family;
    //sa_len = other.sa_len;
}

realSockAddr::realSockAddr(const sockaddr &s) : sockaddr(s) {

}
const std::string &Echo::getMsg() const {
    return msg;
}

void Echo::setMsg(const std::string &msg) {
    Echo::msg = msg;
}