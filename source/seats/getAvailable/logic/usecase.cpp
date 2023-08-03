#include "usecase.h"

GetAvailableSeatsUseCase::GetAvailableSeatsUseCase(
    std::shared_ptr<GetAvailableSeatsRepository> repository) {
    this->repository = repository;
}

std::vector<std::string> GetAvailableSeatsUseCase::execute(std::string &movieId, std::string &theaterId, std::string &sinceDate) {
    return repository->getSeats(movieId, theaterId, sinceDate);
}
