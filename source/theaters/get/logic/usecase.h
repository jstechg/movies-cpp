#ifndef _GET_THEATERS_USE_CASE_H_
#define _GET_THEATERS_USE_CASE_H_

#include <cstdint>
#include <vector>

#include "../data/repository.h"
#include "../domain/theater.h"

#include <memory>

/**
 * @class GetTheatersByMovieUseCase
 * @brief Represents a use case for retrieving theaters showing a specific movie.
 * 
 * This class provides a use case implementation for fetching theaters that are
 * currently showing a specific movie. It utilizes a repository to retrieve theater
 * data based on the movie ID and offers a method to execute the use case, fetching
 * theaters with pagination support.
 */
class GetTheatersByMovieUseCase {
   private:
    std::shared_ptr<GetTheatersByMovieRepository> repository;

   public:
    GetTheatersByMovieUseCase(std::shared_ptr<GetTheatersByMovieRepository> repository);
    virtual ~GetTheatersByMovieUseCase() {}

    /**
     * @brief Executes the use case to retrieve theaters showing a specific movie.
     * @param movieId The unique identifier of the movie.
     * @param page The page number for pagination.
     * @param pageSize The number of theaters per page.
     * @return A vector containing Theater objects representing theaters showing the movie.
     */
    std::vector<Theater> execute(std::string &movieId, uint32_t page, uint32_t pageSize);
};

#endif
