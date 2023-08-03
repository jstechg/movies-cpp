#include "usecase.h"

GetTheatersByMovieUseCase::GetTheatersByMovieUseCase(
    std::shared_ptr<GetTheatersByMovieRepository> repository) {
    this->repository = repository;
}

std::vector<Theater> GetTheatersByMovieUseCase::execute(std::string &movieId,
                                                        uint32_t page,
                                                        uint32_t pageSize) {
    return repository->getTheaters(movieId, page, pageSize);
}
