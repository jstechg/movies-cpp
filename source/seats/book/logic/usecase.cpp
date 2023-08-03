#include "usecase.h"

#include "../../../common/domain/app_error.h"

BookSeatsUseCase::BookSeatsUseCase(
    std::shared_ptr<BookSeatsRepository> repository) {
    this->repository = repository;
}

void BookSeatsUseCase::execute(std::string &movieId, std::string &theaterId,
                               std::string &sinceDate,
                               std::vector<std::string> &seats) {
    auto sessionId = repository->getSessionId(movieId, theaterId, sinceDate);
    if (!sessionId.has_value())
        throw AppError(AppError::ErrorType::NoSessionFound);

    try {
        repository->lockSeats();

        if (!repository->areSeatsAvailable(*sessionId, seats)) {
            throw AppError(AppError::ErrorType::UnavailableSeatsError);
        }

        repository->bookSeats(*sessionId, seats);

        repository->unlockSeats();
    } catch (AppError &exception) {
        repository->unlockSeats();
        throw exception;
    }
}
