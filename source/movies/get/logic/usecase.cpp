#include "usecase.h"

GetMoviesUseCase::GetMoviesUseCase(
    std::shared_ptr<GetMoviesRepository> repository) {
    this->repository = repository;
}

std::vector<Movie> GetMoviesUseCase::execute(uint32_t page, uint32_t pageSize) {
    return repository->getMovies(page, pageSize);
}
