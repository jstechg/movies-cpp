#include "movie.h"

std::map<std::string, DBMovie> DBMovie::Mother::buildMovies(uint32_t size) {
    std::map<std::string, DBMovie> movies;

    for (uint32_t i = 1; i <= size; ++i) {
        DBMovie movie(std::to_string(i), "Movie " + std::to_string(i),
                      "http://example.com/movie_" + std::to_string(i) + ".jpg");

        movies.insert(std::make_pair(movie.getId(), movie));
    }

    return movies;
}
