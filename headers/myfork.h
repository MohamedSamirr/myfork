#ifndef MYFORK_MYFORK_H
#define MYFORK_MYFORK_H

class MyFork {
    bool client;
    bool server;

public:
    MyFork();

    int executeMyForkServer();

    void executeMyForkClient();

    void setClient(bool client);

    void setServer(bool server);

    bool isClient() const;

    bool isServer() const;
};

#endif //MYFORK_MYFORK_H
