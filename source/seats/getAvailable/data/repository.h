#ifndef _SEATS_GET_REPOSITORY_H_
#define _SEATS_GET_REPOSITORY_H_

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../../../common/data/seat.h"
#include "../../common/data/find_session.h"

class GetAvailableSeatsRepository {
   public:
    virtual ~GetAvailableSeatsRepository() {}

    virtual std::vector<std::string> getSeats(std::string &movieId,
                                              std::string &theaterId,
                                              std::string &sinceDate) = 0;
};

class InMemoryGetAvailableSeatsRepository : public GetAvailableSeatsRepository {
   private:
    std::shared_ptr<FindSessionRepository> findSessionRepository;
    std::map<std::string, DBSeat> &seats;

   public:
    InMemoryGetAvailableSeatsRepository(
        std::shared_ptr<FindSessionRepository> findSessionRepository,
        std::map<std::string, DBSeat> &seats)
        : findSessionRepository(findSessionRepository), seats(seats) {}
    virtual ~InMemoryGetAvailableSeatsRepository() {}

    std::vector<std::string> getSeats(std::string &movieId,
                                      std::string &theaterId,
                                      std::string &sinceDate) override;
};

#endif
