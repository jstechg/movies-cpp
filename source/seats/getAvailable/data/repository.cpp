#include "repository.h"

#include "../../../common/domain/app_error.h"

std::vector<std::string> InMemoryGetAvailableSeatsRepository::getSeats(
    std::string& movieId, std::string& theaterId, std::string& sinceDate) {
    auto session =
        findSessionRepository->findSession(movieId, theaterId, sinceDate);
    if (!session.has_value()) {
        throw AppError(AppError::ErrorType::NoSessionFound);
    }

    std::vector<std::string> availableSeats;
    for (const auto& seatPair : seats) {
        auto& seat = seatPair.second;
        if (seat.getSessionId() == (*session).getId() && seat.isAvailable()) {
            availableSeats.push_back(seat.getId());
        }
    }

    return availableSeats;
}
