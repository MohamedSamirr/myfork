#ifndef MYFORK_MESSAGESTRUCTURE_H
#define MYFORK_MESSAGESTRUCTURE_H
#include <vector>
#include <map>
#include <sys/socket.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/array.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <unordered_map>
#include <sstream>

#include "Message.h"

namespace MessageStructures {

    namespace Control {

        struct realSockAddr : public sockaddr {
            friend class boost::serialization::access;

            template<class Archive>
            void serialize(Archive &ar, const unsigned int version) {
                ar & this->sa_data;
                ar & this->sa_family;
                //ar & this->sa_len;
            }

            realSockAddr();

            realSockAddr(const realSockAddr &other);

            realSockAddr(const sockaddr &s);
        };

        struct Echo {
        private:
            std::string msg;

            friend class boost::serialization::access;

            template<class Archive>
            void serialize(Archive &ar, const unsigned int version) {
                ar & msg;
            }

        public:
            const std::string &getMsg() const;

            void setMsg(const std::string &msg);
        };
    }
}


template<typename T>
std::string save(const T &t) {
    std::ostringstream archiveStream;
    boost::archive::text_oarchive archive(archiveStream, boost::archive::no_header);
    archive << t;
    return archiveStream.str();
}

template<typename T>
T load(const std::string &message) {
    T t;
    std::stringstream archiveStream;
    archiveStream << message;
    boost::archive::text_iarchive archive(archiveStream, boost::archive::no_header);
    archive >> t;
    return t;
}


using namespace MessageStructures::Control;

#define OBJECT_SERIALIZATION(T) template std::string save(const T &t); template T load(const std::string &message);
//Echo ICMP
OBJECT_SERIALIZATION(Echo)

OBJECT_SERIALIZATION(Message)

#endif
