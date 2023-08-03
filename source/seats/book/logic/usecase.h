#ifndef _BOOK_SEATS_USE_CASE_H_
#define _BOOK_SEATS_USE_CASE_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../data/repository.h"

/**
 * @class BookSeatsUseCase
 * @brief Represents a use case for booking seats for a movie in a theater.
 * 
 * This class provides a use case implementation for booking seats for a specific
 * movie in a particular theater, starting from a specified date. It utilizes a
 * repository to perform the seat booking operation and offers a method to execute
 * the use case, booking seats based on movie, theater, date, and seat identifiers.
 */
class BookSeatsUseCase {
   private:
    std::shared_ptr<BookSeatsRepository> repository;

   public:
    BookSeatsUseCase(std::shared_ptr<BookSeatsRepository> repository);
    virtual ~BookSeatsUseCase() {}

   /**
     * @brief Executes the use case to book seats for a movie in a theater.
     * @param movieId The unique identifier of the movie.
     * @param theaterId The unique identifier of the theater.
     * @param sinceDate The starting date from which to book seats.
     * @param seats A vector of strings representing the seat identifiers to be booked.
     * @throws AppError If the movie session at that theater is not found or any of the requested seats is already booked.
     */
    void execute(std::string &movieId, std::string &theaterId,
                 std::string &sinceDate, std::vector<std::string> &seats);
};

#endif
