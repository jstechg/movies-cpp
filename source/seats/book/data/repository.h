#ifndef _SEATS_BOOK_REPOSITORY_H_
#define _SEATS_BOOK_REPOSITORY_H_

#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <mutex>
#include "../../common/data/find_session.h"
#include "../../../common/data/seat.h"

class BookSeatsRepository {
    public:
        virtual ~BookSeatsRepository() {}
        
        virtual std::optional<std::string> getSessionId(std::string &movieId, std::string &theaterId, std::string &sinceDate) = 0;
        virtual void lockSeats() = 0;
        virtual void unlockSeats() = 0;
        virtual bool areSeatsAvailable(std::string &sessionId, std::vector<std::string> &seats) = 0;
        virtual void bookSeats(std::string &sessionId, std::vector<std::string> &seats) = 0;
};

class InMemoryBookSeatsRepository: public BookSeatsRepository {
     private:
        std::shared_ptr<FindSessionRepository> findSessionRepository;
        std::mutex &seatsMutex;
        std::map<std::string, DBSeat> &seats;

    public:
        InMemoryBookSeatsRepository(std::shared_ptr<FindSessionRepository> findSessionRepository, std::mutex &seatsMutex, std::map<std::string, DBSeat> &seats) : findSessionRepository(findSessionRepository), seatsMutex(seatsMutex), seats(seats) {}
        virtual ~InMemoryBookSeatsRepository() {}
        
        std::optional<std::string> getSessionId(std::string &movieId, std::string &theaterId, std::string &sinceDate) override;
        void lockSeats() override;
        void unlockSeats() override;
        bool areSeatsAvailable(std::string &sessionId, std::vector<std::string> &seats) override;
        void bookSeats(std::string &sessionId, std::vector<std::string> &seats) override;
};

#endif
