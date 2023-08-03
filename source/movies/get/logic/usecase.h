#ifndef _GET_MOVIES_USE_CASE_H_
#define _GET_MOVIES_USE_CASE_H_

#include <cstdint>
#include <vector>

#include "../data/repository.h"
#include "../domain/movie.h"

#include <memory>

/**
 * @class GetMoviesUseCase
 * @brief Represents a use case for retrieving a list of movies.
 * 
 * This class provides a use case implementation for fetching a list of movies.
 * It utilizes a repository to retrieve movie data and offers a method to execute
 * the use case, fetching movies based on specified pagination parameters.
 */
class GetMoviesUseCase {
   private:
    std::shared_ptr<GetMoviesRepository> repository;

   public:
    GetMoviesUseCase(std::shared_ptr<GetMoviesRepository> repository);
    virtual ~GetMoviesUseCase() {}

    /**
     * @brief Executes the use case to retrieve a list of movies.
     * @param page The page number for pagination.
     * @param pageSize The number of movies per page.
     * @return A vector containing Movie objects retrieved based on pagination parameters.
     */
    std::vector<Movie> execute(uint32_t page, uint32_t pageSize);
};

#endif
