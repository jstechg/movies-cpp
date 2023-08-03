#include "repository.h"
#include "../../../common/data/movie.h"

std::vector<Movie> InMemoryGetMoviesRepository::getMovies(uint32_t page, uint32_t pageSize) {
    int startIndex = (page - 1) * pageSize;
    int endIndex = startIndex + pageSize;

    std::vector<Movie> paginatedMovies;
    int count = 0;

    for (const auto& entry : movies) {
        if (count >= startIndex && count < endIndex) {
            Movie movie = Movie(entry.second.getId(), entry.second.getTitle(), entry.second.getImageUrl());
            paginatedMovies.push_back(movie);
        }
        count++;
    }

    return paginatedMovies;
}
