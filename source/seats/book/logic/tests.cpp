#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../common/domain/app_error.h"
#include "usecase.h"

using ::testing::_;
using ::testing::Return;

class BookSeatsUseCaseTest : public testing::Test {
   protected:
    class MockBookSeatsRepository : public BookSeatsRepository {
       public:
        MOCK_METHOD3(getSessionId,
                     std::optional<std::string>(std::string& movieId,
                                                std::string& theaterId,
                                                std::string& sinceDate));
        MOCK_METHOD0(lockSeats, void());
        MOCK_METHOD0(unlockSeats, void());
        MOCK_METHOD2(areSeatsAvailable, bool(std::string& sessionId,
                                             std::vector<std::string>& seats));
        MOCK_METHOD2(bookSeats, void(std::string& sessionId,
                                     std::vector<std::string>& seats));
    };
};

TEST_F(BookSeatsUseCaseTest, SessionNotFound) {
    // Arrange
    auto repository = std::make_shared<MockBookSeatsRepository>();
    BookSeatsUseCase usecase(repository);
    std::string movieId = "1";
    std::string theaterId = "2";
    std::string sinceDate = "2023-08-01T10:00:00Z";
    std::vector<std::string> seats = {"a1", "a2", "a3"};
    EXPECT_CALL(*repository, getSessionId(movieId, theaterId, sinceDate))
        .WillOnce(testing::Return(std::nullopt));

    try {
        // Act
        usecase.execute(movieId, theaterId, sinceDate, seats);
    } catch (AppError& error) {
        // Assert
        EXPECT_EQ(error.getErrorType(), AppError::ErrorType::NoSessionFound);
        testing::Mock::VerifyAndClearExpectations(&repository);
    }
}

TEST_F(BookSeatsUseCaseTest, SeatsNotAvailable) {
    // Arrange
    auto repository = std::make_shared<MockBookSeatsRepository>();
    BookSeatsUseCase usecase(repository);
    std::string movieId = "1";
    std::string theaterId = "2";
    std::string sinceDate = "2023-08-01T10:00:00Z";
    std::string sessionId = "3";
    std::vector<std::string> seats = {"a1", "a2", "a3"};
    EXPECT_CALL(*repository, getSessionId(movieId, theaterId, sinceDate))
        .WillOnce(testing::Return(std::optional(sessionId)));
    EXPECT_CALL(*repository, areSeatsAvailable(sessionId, seats))
        .WillOnce(testing::Return(false));
    EXPECT_CALL(*repository, bookSeats(sessionId, seats))
        .Times(testing::Exactly(0));
    EXPECT_CALL(*repository, lockSeats()).Times(testing::Exactly(1));
    EXPECT_CALL(*repository, unlockSeats()).Times(testing::Exactly(1));

    try {
        // Act
        usecase.execute(movieId, theaterId, sinceDate, seats);
    } catch (AppError& error) {
        // Assert
        EXPECT_EQ(error.getErrorType(),
                  AppError::ErrorType::UnavailableSeatsError);
        testing::Mock::VerifyAndClearExpectations(&repository);
    }
}

TEST_F(BookSeatsUseCaseTest, HappyPath) {
    // Arrange
    auto repository = std::make_shared<MockBookSeatsRepository>();
    BookSeatsUseCase usecase(repository);
    std::string movieId = "1";
    std::string theaterId = "2";
    std::string sinceDate = "2023-08-01T10:00:00Z";
    std::string sessionId = "3";
    std::vector<std::string> seats = {"a1", "a2", "a3"};
    EXPECT_CALL(*repository, getSessionId(movieId, theaterId, sinceDate))
        .WillOnce(testing::Return(std::optional(sessionId)));
    EXPECT_CALL(*repository, areSeatsAvailable(sessionId, seats))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*repository, bookSeats(sessionId, seats))
        .Times(testing::Exactly(1));
    EXPECT_CALL(*repository, lockSeats()).Times(testing::Exactly(1));
    EXPECT_CALL(*repository, unlockSeats()).Times(testing::Exactly(1));

    // Act
    usecase.execute(movieId, theaterId, sinceDate, seats);

    // Assert
    testing::Mock::VerifyAndClearExpectations(&repository);
}
