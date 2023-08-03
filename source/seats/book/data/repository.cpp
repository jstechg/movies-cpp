#include "repository.h"

#include "../../../common/data/seat.h"

std::optional<std::string> InMemoryBookSeatsRepository::getSessionId(
    std::string &movieId, std::string &theaterId, std::string &sinceDate) {
    auto result =
        findSessionRepository->findSession(movieId, theaterId, sinceDate);
    if (!result.has_value()) return std::nullopt;
    return (*result).getId();
}

void InMemoryBookSeatsRepository::lockSeats() {
    // Let's lock the whole seats table for sake of development time. An
    // optimization which could be made is to lock only seats belonging to a
    // specific sessionId
    seatsMutex.lock();
}

void InMemoryBookSeatsRepository::unlockSeats() {
    seatsMutex.unlock();
}

bool InMemoryBookSeatsRepository::areSeatsAvailable(
    std::string &sessionId, std::vector<std::string> &seats) {
    for (const std::string &seatId : seats) {
        auto seatIt = this->seats.find(seatId);
        if (seatIt == this->seats.end()) {
            return false;
        }

        auto &seat = seatIt->second;
        if (seat.getSessionId() != sessionId || !seat.isAvailable()) {
            return false;
        }
    }

    return true;
}

void InMemoryBookSeatsRepository::bookSeats(std::string &sessionId,
                                            std::vector<std::string> &seats) {
    for (auto &seatId : seats) {
        auto seatIt = this->seats.find(seatId);
        if (seatIt != this->seats.end()) {
            auto &seat = seatIt->second;
            if (seat.getSessionId() == sessionId) {
                seat.setAvailable(false);
            }
        }
    }
}
