#include <unistd.h>
#include "../headers/myfork.h"

MyFork::MyFork() {
    this->client = false;
    this->server = false;
}

bool MyFork::isClient() const {
    return client;
}

bool MyFork::isServer() const {
    return server;
}

void MyFork::setClient(bool client) {
    MyFork::client = client;
}

void MyFork::setServer(bool server) {
    MyFork::server = server;
}

int MyFork::executeMyForkServer() {
    this->setServer(true);

    pid_t pid = fork();

    if(pid < 0)
        throw "Cannot create child process";

    if(pid == 0) {
        sleep(10);
        return 1;
    } else {
        return pid;
    }
}

void MyFork::executeMyForkClient() {
    this->setClient(true);
}
