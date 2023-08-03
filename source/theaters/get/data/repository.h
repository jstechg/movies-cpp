#ifndef _THEATERS_GET_REPOSITORY_H_
#define _THEATERS_GET_REPOSITORY_H_

#include <vector>

#include "../domain/theater.h"
#include "../../../common/data/theater.h"
#include "../../../common/data/session.h"

class GetTheatersByMovieRepository {
   public:
    virtual ~GetTheatersByMovieRepository() {}

    virtual std::vector<Theater> getTheaters(std::string &movieId,
                                             uint32_t page,
                                             uint32_t pageSize) = 0;
};

class InMemoryGetTheatersByMovieRepository
    : public GetTheatersByMovieRepository {
   private:
    std::map<std::string, DBTheater>& theaters;
    std::map<std::string, DBSession>& sessions;

   public:
    InMemoryGetTheatersByMovieRepository(std::map<std::string, DBTheater>& theaters,
    std::map<std::string, DBSession>& sessions): theaters(theaters), sessions(sessions) {}
    virtual ~InMemoryGetTheatersByMovieRepository() {}

    std::vector<Theater> getTheaters(std::string &movieId, uint32_t page,
                                     uint32_t pageSize) override;
};

#endif
