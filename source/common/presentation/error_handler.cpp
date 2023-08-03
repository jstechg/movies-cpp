#include "error_handler.h"

void handleAppError(AppError &error, httplib::Response &res) {
    switch (error.getErrorType()) {
        case AppError::ErrorType::ValidationError:
            res.status = 400;
            res.set_content("Validation error", "text/plain");
            break;
        case AppError::ErrorType::UnavailableSeatsError:
            res.status = 422;
            res.set_content("The specified seats are not available",
                            "text/plain");
            break;
        case AppError::ErrorType::NoSessionFound:
            res.status = 404;
            res.set_content("No session found", "text/plain");
            break;
    }
}
