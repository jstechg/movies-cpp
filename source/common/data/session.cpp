#include "session.h"

std::map<std::string, DBSession> DBSession::Mother::buildSessions(
    std::map<std::string, DBMovie>& movies,
    std::map<std::string, DBTheater>& theaters, uint32_t numSessions) {
    std::map<std::string, DBSession> result;

    for (const auto& moviePair : movies) {
        const std::string& movieId = moviePair.first;

        for (const auto& theaterPair : theaters) {
            const std::string& theaterId = theaterPair.first;

            for (uint32_t sessionNumber = 1; sessionNumber <= numSessions;
                 ++sessionNumber) {
                std::string sessionId = movieId + "_" + theaterId + "_" +
                                        std::to_string(sessionNumber);

                std::string startDate = "2023-07-31T12:00:00Z";
                std::string endDate = "2023-07-31T14:00:00Z";

                DBSession session(sessionId, startDate, endDate, theaterId,
                                  movieId);
                result.insert(std::make_pair(sessionId, session));
            }
        }
    }

    return result;
}
