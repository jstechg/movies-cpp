#ifndef _GET_SEATS_USE_CASE_H_
#define _GET_SEATS_USE_CASE_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../data/repository.h"

/**
 * @class GetAvailableSeatsUseCase
 * @brief Represents a use case for retrieving available seats for a movie in a theater.
 * 
 * This class provides a use case implementation for fetching available seats for a
 * specific movie in a particular theater, starting from a specified date. It utilizes
 * a repository to retrieve seat availability data and offers a method to execute the
 * use case, fetching available seats based on movie, theater, and date.
 */
class GetAvailableSeatsUseCase {
   private:
    std::shared_ptr<GetAvailableSeatsRepository> repository;

   public:
    GetAvailableSeatsUseCase(
        std::shared_ptr<GetAvailableSeatsRepository> repository);
    virtual ~GetAvailableSeatsUseCase() {}

    /**
     * @brief Executes the use case to retrieve available seats for a movie in a theater.
     * @param movieId The unique identifier of the movie.
     * @param theaterId The unique identifier of the theater.
     * @param sinceDate The starting date from which to retrieve available seats.
     * @return A vector of strings representing the available seat identifiers.
     */
    std::vector<std::string> execute(std::string &movieId,
                                     std::string &theaterId,
                                     std::string &sinceDate);
};

#endif
