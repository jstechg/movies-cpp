#ifndef _COMMON_DATA_SESSION_H_
#define _COMMON_DATA_SESSION_H_

#include <map>
#include <string>

#include "movie.h"
#include "theater.h"

class DBSession {
   private:
    std::string id;
    std::string startDate;
    std::string endDate;
    std::string theaterId;
    std::string movieId;

   public:
    DBSession(const std::string& id, const std::string& startDate,
              const std::string& endDate, const std::string& theaterId,
              const std::string& movieId)
        : id(id),
          startDate(startDate),
          endDate(endDate),
          theaterId(theaterId),
          movieId(movieId) {}

    std::string getId() const { return id; }
    std::string getStartDate() const { return startDate; }
    std::string getEndDate() const { return endDate; }
    std::string getTheaterId() const { return theaterId; }
    std::string getMovieId() const { return movieId; }

    void setId(const std::string& id) { this->id = id; }
    void setStartDate(const std::string& startDate) {
        this->startDate = startDate;
    }
    void setEndDate(const std::string& endDate) { this->endDate = endDate; }
    void setTheaterId(const std::string& theaterId) {
        this->theaterId = theaterId;
    }
    void setMovieId(const std::string& movieId) { this->movieId = movieId; }

    class Mother {
       public:
        static std::map<std::string, DBSession> buildSessions(
            std::map<std::string, DBMovie>& movies,
            std::map<std::string, DBTheater>& theaters, uint32_t numSessions);
    };
};

#endif
