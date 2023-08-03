#include <gtest/gtest.h>

#include "repository.h"

class InMemoryGetTheatersByMovieRepositoryTest : public testing::Test {
   protected:
    std::map<std::string, DBTheater> dbTheaters = DBTheater::Mother::buildTheaters(8);
    std::map<std::string, DBSession> dbSessions = {
        {"1", DBSession("1", "startDate", "endDate", "1", "1")},
        {"2", DBSession("2", "startDate", "endDate", "2", "1")},
        {"3", DBSession("3", "startDate", "endDate", "3", "2")},
        {"4", DBSession("4", "startDate", "endDate", "4", "2")},
        {"5", DBSession("5", "startDate", "endDate", "5", "2")}};
};

TEST_F(InMemoryGetTheatersByMovieRepositoryTest, CorrectMovieMatch) {
    // Arrange
    InMemoryGetTheatersByMovieRepository repository(dbTheaters, dbSessions);

    // Act
    std::string movieId = "2";
    auto theaters = repository.getTheaters(movieId, 1, 5);

    // Assert
    EXPECT_EQ(theaters.size(), 3);
    EXPECT_EQ(theaters[0].getId(), "3");
    EXPECT_EQ(theaters[1].getId(), "4");
    EXPECT_EQ(theaters[2].getId(), "5");
}

TEST_F(InMemoryGetTheatersByMovieRepositoryTest, NotFoundCase) {
    // Arrange
    InMemoryGetTheatersByMovieRepository repository(dbTheaters, dbSessions);

    // Act
    std::string movieId = "3";
    auto theaters = repository.getTheaters(movieId, 1, 2);

    // Assert
    EXPECT_EQ(theaters.size(), 0);
}

TEST_F(InMemoryGetTheatersByMovieRepositoryTest, PaginationWorks) {
    // Arrange
    InMemoryGetTheatersByMovieRepository repository(dbTheaters, dbSessions);

    // Act
    std::string movieId = "2";
    auto theaters = repository.getTheaters(movieId, 2, 2);

    // Assert
    EXPECT_EQ(theaters.size(), 1);
    EXPECT_EQ(theaters[0].getId(), "5");
}

TEST_F(InMemoryGetTheatersByMovieRepositoryTest, PaginationOutOfBounds) {
    // Arrange
    InMemoryGetTheatersByMovieRepository repository(dbTheaters, dbSessions);

    // Act
    std::string movieId = "2";
    auto theaters = repository.getTheaters(movieId, 3, 2);

    // Assert
    EXPECT_EQ(theaters.size(), 0);
}
