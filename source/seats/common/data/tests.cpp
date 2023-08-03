#include <gtest/gtest.h>

#include "find_session.h"

class InMemoryFindSessionRepositoryTest : public testing::Test {
   protected:
    std::map<std::string, DBSession> dbSessions = {
        {"1", DBSession("1", "2023-08-01T10:00:00Z", "2023-08-01T11:00:00Z",
                        "1", "1")},
        {"2", DBSession("2", "2023-08-01T12:00:00Z", "2023-08-01T13:00:00Z",
                        "2", "1")},
        {"3", DBSession("3", "2023-08-01T10:00:00Z", "2023-08-01T11:00:00Z",
                        "3", "2")},
        {"4", DBSession("4", "2023-08-01T12:00:00Z", "2023-08-01T13:00:00Z",
                        "4", "2")},
        {"5", DBSession("5", "2023-08-01T15:00:00Z", "2023-08-01T16:00:00Z",
                        "5", "2")}};
};

TEST_F(InMemoryFindSessionRepositoryTest, FindSessionDateBetween) {
    // Arrange
    InMemoryFindSessionRepository repository(dbSessions);

    // Act
    std::string movieId = "1";
    std::string theaterId = "1";
    std::string sinceDate = "2023-08-01T10:30:00Z";
    auto session = repository.findSession(movieId, theaterId, sinceDate);

    // Assert
    EXPECT_EQ(session.has_value(), true);
    EXPECT_EQ((*session).getId(), "1");
}

TEST_F(InMemoryFindSessionRepositoryTest, NotFoundMovieTheater) {
    // Arrange
    InMemoryFindSessionRepository repository(dbSessions);

    // Act
    std::string movieId = "1";
    std::string theaterId = "3";
    std::string sinceDate = "2023-08-01T10:30:00Z";
    auto session = repository.findSession(movieId, theaterId, sinceDate);

    // Assert
    EXPECT_EQ(session.has_value(), false);
}

TEST_F(InMemoryFindSessionRepositoryTest, FindSessionDateBefore) {
    // Arrange
    InMemoryFindSessionRepository repository(dbSessions);

    // Act
    std::string movieId = "1";
    std::string theaterId = "1";
    std::string sinceDate = "2023-08-01T09:30:00Z";
    auto session = repository.findSession(movieId, theaterId, sinceDate);

    // Assert
    EXPECT_EQ(session.has_value(), true);
    EXPECT_EQ((*session).getId(), "1");
}

TEST_F(InMemoryFindSessionRepositoryTest, FindSessionDateAfter) {
    // Arrange
    InMemoryFindSessionRepository repository(dbSessions);

    // Act
    std::string movieId = "1";
    std::string theaterId = "1";
    std::string sinceDate = "2023-08-01T12:30:00Z";
    auto session = repository.findSession(movieId, theaterId, sinceDate);

    // Assert
    EXPECT_EQ(session.has_value(), false);
}
