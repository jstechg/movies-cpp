#include "controller.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "../../../common/domain/app_error.h"
#include "../../../common/presentation/error_handler.h"

GetTheatersController::GetTheatersController(
    std::shared_ptr<httplib::Server> server,
    std::shared_ptr<GetTheatersByMovieUseCase> usecase) {
    this->server = server;
    this->usecase = usecase;
}

GetTheatersController::Input GetTheatersController::deserializeInput(
    const httplib::Request& req) {
    Input input;

    try {
        if (!req.has_param("movieId")) {
            throw AppError(AppError::ErrorType::ValidationError);
        }

        input.movieId = req.get_param_value("movieId");

        if (!req.has_param("page")) {
            throw AppError(AppError::ErrorType::ValidationError);
        }

        input.page = std::stoul(req.get_param_value("page"));

        if (!req.has_param("pageSize")) {
            throw AppError(AppError::ErrorType::ValidationError);
        }

        input.pageSize = std::stoul(req.get_param_value("pageSize"));

        return input;
    } catch (const std::invalid_argument&) {
        throw AppError(AppError::ErrorType::ValidationError);
    }
}

std::string GetTheatersController::serializeResponse(
    const std::vector<Theater>& theaters) {
    rapidjson::Document document;
    document.SetArray();

    for (const auto& theater : theaters) {
        rapidjson::Value theaterObj(rapidjson::kObjectType);
        auto& allocator = document.GetAllocator();
        theaterObj.AddMember(
            "id", rapidjson::Value(theater.getId().c_str(), allocator),
            allocator);
        theaterObj.AddMember(
            "name", rapidjson::Value(theater.getName().c_str(), allocator),
            allocator);
        document.PushBack(theaterObj, document.GetAllocator());
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

void GetTheatersController::registerRoute() {
    server->Get("/api/theaters", [&](const httplib::Request& req,
                                     httplib::Response& res) {
        try {
            auto input = deserializeInput(req);
            auto response = usecase->execute(input.movieId, input.page, input.pageSize);
            res.set_content(serializeResponse(response), "application/json");
        } catch (AppError& error) {
            handleAppError(error, res);
        }
    });
}
