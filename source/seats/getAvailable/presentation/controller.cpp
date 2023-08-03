#include "controller.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "../../../common/domain/app_error.h"
#include "../../../common/presentation/error_handler.h"

GetAvailableSeatsController::GetAvailableSeatsController(
    std::shared_ptr<httplib::Server> server,
    std::shared_ptr<GetAvailableSeatsUseCase> usecase) {
    this->server = server;
    this->usecase = usecase;
}

GetAvailableSeatsController::Input
GetAvailableSeatsController::deserializeInput(const httplib::Request& req) {
    Input input;

    if (!req.has_param("movieId")) {
        throw AppError(AppError::ErrorType::ValidationError);
    }

    input.movieId = req.get_param_value("movieId");

    if (!req.has_param("theaterId")) {
        throw AppError(AppError::ErrorType::ValidationError);
    }

    input.theaterId = req.get_param_value("theaterId");

    if (!req.has_param("sinceDate")) {
        throw AppError(AppError::ErrorType::ValidationError);
    }

    input.sinceDate = req.get_param_value("sinceDate");

    return input;
}

std::string GetAvailableSeatsController::serializeResponse(
    const std::vector<std::string>& seats) {
    rapidjson::Document document;
    document.SetArray();

    for (const auto& str : seats) {
        rapidjson::Value strValue;
        strValue.SetString(str.c_str(),
                           static_cast<rapidjson::SizeType>(str.length()),
                           document.GetAllocator());
        document.PushBack(strValue, document.GetAllocator());
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

void GetAvailableSeatsController::registerRoute() {
    server->Get("/api/seats", [&](const httplib::Request& req,
                                   httplib::Response& res) {
        try {
            auto input = deserializeInput(req);
            auto response = usecase->execute(input.movieId, input.theaterId, input.sinceDate);
            res.set_content(serializeResponse(response), "application/json");
        } catch (AppError& error) {
            handleAppError(error, res);
        }
    });
}
