#include <cstdlib>
#include <utility>
#include "../headers/Message.h"
#include "../headers/MessageStructure.h"

Message::Message() {}

Message::Message(Message::MessageType messageType, Message::OperationType operation, std::string message,
                 size_t messageSize,
                 Message::RPC_ID rpcId) {
    this->operation = operation;
    this->messageType = messageType;
    this->message = std::move(message);
    this->messageSize = messageSize;
    this->rpcId = rpcId;
}

Message::Message(char *message) {
    auto msg = load<Message>(message);
    *this = msg;
}

std::string Message::serialize() const {
    std::string serialized = save<Message>(*this);
    return serialized;
}

int Message::getOperation() {
    return this->operation;
}

Message::RPC_ID Message::getRPCId() {
    return this->rpcId;
}

std::string Message::getMessage() {
    return this->message;
}

size_t Message::getMessageSize() {
    return this->messageSize;
}

Message::MessageType Message::getMessageType() {
    return this->messageType;
}

void Message::setOperation(OperationType _operation) {
    this->operation = _operation;
}

void Message::setMessage(std::string message, size_t message_size) {
    this->message = message;
    this->messageSize = message_size;
}

void Message::setMessageType(MessageType message_type) {
    this->messageType = message_type;
}

Message::~Message() {
}

int Message::RPC_ID::currentMessageId = 0;

