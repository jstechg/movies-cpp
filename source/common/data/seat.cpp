#include "seat.h"

std::map<std::string, DBSeat> DBSeat::Mother::buildSeats(
    std::map<std::string, DBSession>& sessions, uint32_t numSeats, bool available) {
    std::map<std::string, DBSeat> result;

    for (const auto& sessionPair : sessions) {
        const std::string& sessionId = sessionPair.first;

        for (uint32_t seatNumber = 1; seatNumber <= numSeats; ++seatNumber) {
            std::string seatId = "a" + std::to_string(seatNumber);
            DBSeat seat(seatId, sessionId, available);
            result.insert(std::make_pair(seatId, seat));
        }
    }

    return result;
}
