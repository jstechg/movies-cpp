#ifndef _MOVIES_GET_REPOSITORY_H_
#define _MOVIES_GET_REPOSITORY_H_

#include <vector>

#include "../../../common/data/movie.h"
#include "../domain/movie.h"

class GetMoviesRepository {
   public:
    virtual ~GetMoviesRepository() {}

    virtual std::vector<Movie> getMovies(uint32_t page, uint32_t pageSize) = 0;
};

class InMemoryGetMoviesRepository : public GetMoviesRepository {
   private:
    std::map<std::string, DBMovie>& movies;

   public:
    InMemoryGetMoviesRepository(std::map<std::string, DBMovie>& movies)
        : movies(movies) {}
    virtual ~InMemoryGetMoviesRepository() {}

    std::vector<Movie> getMovies(uint32_t page, uint32_t pageSize) override;
};

#endif
