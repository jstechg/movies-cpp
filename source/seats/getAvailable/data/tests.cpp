#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../common/domain/app_error.h"
#include "repository.h"

using ::testing::_;
using ::testing::Return;

class InMemoryGetAvailableSeatsRepositoryTest : public testing::Test {
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

TEST_F(InMemoryGetAvailableSeatsRepositoryTest, SessionNotFound) {
    // Arrange
    auto findSessionRepository = std::make_shared<MockFindSessionRepository>();
    auto seats = DBSeat::Mother::buildSeats(dbSessions, 5);
    InMemoryGetAvailableSeatsRepository repository(findSessionRepository,
                                                   seats);
    std::string movieId = "1";
    std::string theaterId = "1";
    std::string sinceDate = "2023-08-01T10:30:00Z";
    EXPECT_CALL(*findSessionRepository.get(),
                findSession(movieId, theaterId, sinceDate))
        .WillOnce(Return(std::nullopt));

    // Act
    EXPECT_THROW(repository.getSeats(movieId, theaterId, sinceDate), AppError);

    // Assert
    testing::Mock::VerifyAndClearExpectations(&repository);
}

TEST_F(InMemoryGetAvailableSeatsRepositoryTest, GetSingleAvailableSeat) {
    // Arrange
    std::string seatId = "a5";
    std::string movieId = "1";
    std::string theaterId = "1";
    std::string sinceDate = "2023-08-01T10:30:00Z";
    auto dbSeats = DBSeat::Mother::buildSeats(dbSessions, 20, false);
    dbSeats.at(seatId).setAvailable(true);
    auto findSessionRepository = std::make_shared<MockFindSessionRepository>();
    InMemoryGetAvailableSeatsRepository repository(findSessionRepository,
                                                   dbSeats);
    EXPECT_CALL(*findSessionRepository.get(),
                findSession(movieId, theaterId, sinceDate))
        .WillOnce(Return(std::optional(dbSessions.at("1"))));

    // Act
    auto seats = repository.getSeats(movieId, theaterId, sinceDate);

    // Assert
    EXPECT_EQ(seats.size(), 1);
    EXPECT_EQ(seats[0], seatId);
    testing::Mock::VerifyAndClearExpectations(&repository);
}
