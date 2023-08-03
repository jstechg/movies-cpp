#include "controller.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "../../../common/domain/app_error.h"
#include "../../../common/presentation/error_handler.h"

BookSeatsController::BookSeatsController(
    std::shared_ptr<httplib::Server> server,
    std::shared_ptr<BookSeatsUseCase> usecase) {
    this->server = server;
    this->usecase = usecase;
}

BookSeatsController::Input
BookSeatsController::deserializeInput(const httplib::Request& req) {
    Input input;

    rapidjson::Document document;
    document.Parse(req.body.c_str());

    if (document.HasParseError()) {
        throw AppError(AppError::ErrorType::ValidationError);
    }

    if (!document.HasMember("movieId") || !document["movieId"].IsString()) {
        throw AppError(AppError::ErrorType::ValidationError);
    }
    input.movieId = document["movieId"].GetString();

    if (!document.HasMember("theaterId") || !document["theaterId"].IsString()) {
        throw AppError(AppError::ErrorType::ValidationError);
    }
    input.theaterId = document["theaterId"].GetString();

    if (!document.HasMember("sinceDate") || !document["sinceDate"].IsString()) {
        throw AppError(AppError::ErrorType::ValidationError);
    }
    input.sinceDate = document["sinceDate"].GetString();

    if (!document.HasMember("seats") || !document["seats"].IsArray()) {
        throw AppError(AppError::ErrorType::ValidationError);
    }

    const rapidjson::Value& seatsArray = document["seats"];
    for (rapidjson::SizeType i = 0; i < seatsArray.Size(); ++i) {
        if (seatsArray[i].IsString()) {
            input.seats.push_back(seatsArray[i].GetString());
        } else {
            throw AppError(AppError::ErrorType::ValidationError);
        }
    }

    return input;
}

void BookSeatsController::registerRoute() {
    server->Get("/api/seats", [&](const httplib::Request& req,
                                   httplib::Response& res) {
        try {
            auto input = deserializeInput(req);
            usecase->execute(input.movieId, input.theaterId, input.sinceDate, input.seats);
            res.status = 200;
            res.set_content("Seats locked successfully", "text/plain");
        } catch (AppError& error) {
            handleAppError(error, res);
        }
    });
}
