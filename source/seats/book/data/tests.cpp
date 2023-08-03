#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "repository.h"

using ::testing::_;
using ::testing::Return;

class InMemoryBookSeatsRepositoryTest : public testing::Test {
   protected:
    std::map<std::string, DBSession> dbSessions = {
        {"1", DBSession("1", "2023-08-01T10:00:00Z", "2023-08-01T11:00:00Z",
                        "1", "1")}};

    class MockFindSessionRepository : public FindSessionRepository {
       public:
        MOCK_METHOD3(findSession,
                     std::optional<DBSession>(std::string& movieId,
                                              std::string& theaterId,
                                              std::string& sinceDate));
    };
};

TEST_F(InMemoryBookSeatsRepositoryTest, SeatsAvailable) {
    // Arrange
    auto findSessionRepository = std::make_shared<MockFindSessionRepository>();
    auto seats = DBSeat::Mother::buildSeats(dbSessions, 5);
    auto mutex = std::mutex();
    InMemoryBookSeatsRepository repository(findSessionRepository, mutex, seats);
    std::string sessionId = "1";
    std::vector<std::string> requestedSeats = {"a1", "a2", "a3", "a4", "a5"};

    // Act
    bool available = repository.areSeatsAvailable(sessionId, requestedSeats);

    // Assert
    EXPECT_TRUE(available);
}

TEST_F(InMemoryBookSeatsRepositoryTest, SeatsNotAvailable) {
    // Arrange
    auto findSessionRepository = std::make_shared<MockFindSessionRepository>();
    auto seats = DBSeat::Mother::buildSeats(dbSessions, 5);
    seats.at("a1").setAvailable(false);
    auto mutex = std::mutex();
    InMemoryBookSeatsRepository repository(findSessionRepository, mutex, seats);
    std::string sessionId = "1";
    std::vector<std::string> requestedSeats = {"a1"};

    // Act
    bool available = repository.areSeatsAvailable(sessionId, requestedSeats);

    // Assert
    EXPECT_FALSE(available);
}

TEST_F(InMemoryBookSeatsRepositoryTest, BookSingleSeat) {
    // Arrange
    auto findSessionRepository = std::make_shared<MockFindSessionRepository>();
    auto seats = DBSeat::Mother::buildSeats(dbSessions, 5);
    auto mutex = std::mutex();
    InMemoryBookSeatsRepository repository(findSessionRepository, mutex, seats);
    std::string sessionId = "1";
    std::vector<std::string> requestedSeats = {"a1"};

    // Act
    repository.bookSeats(sessionId, requestedSeats);

    // Assert
    EXPECT_FALSE(seats.at("a1").isAvailable());
}

TEST_F(InMemoryBookSeatsRepositoryTest, BookMultipleSeats) {
    // Arrange
    auto findSessionRepository = std::make_shared<MockFindSessionRepository>();
    auto seats = DBSeat::Mother::buildSeats(dbSessions, 5);
    auto mutex = std::mutex();
    InMemoryBookSeatsRepository repository(findSessionRepository, mutex, seats);
    std::string sessionId = "1";
    std::vector<std::string> requestedSeats = {"a1", "a2"};

    // Act
    repository.bookSeats(sessionId, requestedSeats);

    // Assert
    EXPECT_FALSE(seats.at("a1").isAvailable() || seats.at("a2").isAvailable());
}
