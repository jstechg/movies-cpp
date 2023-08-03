#ifndef _APP_ERROR_H_
#define _APP_ERROR_H_

#include <exception>
#include <string>

/**
 * @class AppError
 * @brief Represents an application-specific error that can occur during runtime.
 * 
 * This class derives from std::exception and provides an enum class for defining
 * different types of application errors. It allows encapsulating and identifying
 * various error scenarios that may arise within the application.
 */
class AppError : public std::exception {
public:
    /**
     * @brief Enum class defining different types of application errors.
     */
    enum class ErrorType {
        ValidationError,
        UnavailableSeatsError,
        NoSessionFound
    };

    AppError(ErrorType errorType) : errorType(errorType) {}

    /**
     * @brief Retrieves the type of the error.
     * @return The ErrorType enum value representing the type of the error.
     */
    ErrorType getErrorType() { return errorType; }

private:
    ErrorType errorType;
};

#endif
