#include <gtest/gtest.h>

#include "repository.h"

TEST(InMemoryGetMoviesRepositoryTest, EmptyRepositoryTest) {
    // Arrange
    auto dbMovies = DBMovie::Mother::buildMovies(10);
    InMemoryGetMoviesRepository repository(dbMovies);

    // Act
    auto movies = repository.getMovies(0, 0);

    // Assert
    EXPECT_TRUE(movies.empty());
}

TEST(InMemoryGetMoviesRepositoryTest, FetchesFirstPage) {
    // Arrange
    auto dbMovies = DBMovie::Mother::buildMovies(10);
    InMemoryGetMoviesRepository repository(dbMovies);

    // Act
    auto movies = repository.getMovies(1, 5);

    // Assert
    EXPECT_EQ(movies.size(), 5);
    EXPECT_EQ(movies[0].getId(), "1");
}

TEST(InMemoryGetMoviesRepositoryTest, FetchesMiddlePage) {
    // Arrange
    auto dbMovies = DBMovie::Mother::buildMovies(10);
    InMemoryGetMoviesRepository repository(dbMovies);

    // Act
    auto movies = repository.getMovies(2, 3);

    // Assert
    EXPECT_EQ(movies.size(), 3);
    EXPECT_EQ(movies[0].getId(), "3");
}
