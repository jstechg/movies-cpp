#ifndef _COMMON_DATA_SEAT_H_
#define _COMMON_DATA_SEAT_H_

#include <map>
#include <string>

#include "session.h"

class DBSeat {
   private:
    std::string id;
    std::string sessionId;
    bool available;

   public:
    DBSeat(const std::string& id, const std::string& sessionId, bool available)
        : id(id), sessionId(sessionId), available(available) {}

    std::string getId() const { return id; }
    std::string getSessionId() const { return sessionId; }
    bool isAvailable() const { return available; }

    void setId(const std::string& id) { this->id = id; }
    void setSessionId(const std::string& sessionId) {
        this->sessionId = sessionId;
    }
    void setAvailable(bool available) { this->available = available; }

    class Mother {
       public:
        static std::map<std::string, DBSeat> buildSeats(
            std::map<std::string, DBSession>& sessions, uint32_t numSeats, bool available = true);
    };
};

#endif
