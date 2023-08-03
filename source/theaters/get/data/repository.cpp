#include "repository.h"

#include "../../../common/data/session.h"
#include "../../../common/data/theater.h"

std::vector<Theater> InMemoryGetTheatersByMovieRepository::getTheaters(
    std::string& movieId, uint32_t page, uint32_t pageSize) {
    std::vector<Theater> theaters;
    for (const auto& sessionPair : sessions) {
        auto& session = sessionPair.second;
        if (session.getMovieId() != movieId) continue;

        auto theaterIt = this->theaters.find(session.getTheaterId());
        if (theaterIt != this->theaters.end()) {
            theaters.push_back(Theater(theaterIt->second.getId(), theaterIt->second.getName()));
        }
    }

    std::vector<Theater> paginatedTheaters;

    uint32_t startIndex = (page - 1) * pageSize;
    uint32_t endIndex = startIndex + pageSize;

    if (startIndex >= theaters.size()) {
        return paginatedTheaters;
    }

    if (endIndex > theaters.size()) {
        endIndex = theaters.size();
    }

    for (uint32_t i = startIndex; i < endIndex; i++) {
        paginatedTheaters.push_back(theaters[i]);
    }

    return paginatedTheaters;
}
