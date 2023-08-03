#include "find_session.h"

#include <ctime>
#include <iomanip>
#include <iostream>

bool InMemoryFindSessionRepository::isDateAfter(const std::string& first,
                                                const std::string& second) {
    std::tm firstDate = {};
    std::tm secondDate = {};

    std::istringstream firstDateStream(first);
    firstDateStream >> std::get_time(&firstDate, "%Y-%m-%dT%H:%M:%SZ");

    std::istringstream secondDateStream(second);
    secondDateStream >> std::get_time(&secondDate, "%Y-%m-%dT%H:%M:%SZ");

    return std::mktime(&firstDate) > std::mktime(&secondDate);
}

std::optional<DBSession> InMemoryFindSessionRepository::findSession(
    std::string& movieId, std::string& theaterId, std::string& sinceDate) {
    for (const auto& sessionPair : sessions) {
        auto& session = sessionPair.second;
        if (session.getMovieId() == movieId &&
            session.getTheaterId() == theaterId &&
            isDateAfter(session.getEndDate(), sinceDate)) {
            return std::optional(session);
        }
    }
    return std::nullopt;
}
