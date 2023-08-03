#include "controller.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "../../../common/domain/app_error.h"
#include "../../../common/presentation/error_handler.h"

GetMoviesController::GetMoviesController(
    std::shared_ptr<httplib::Server> server,
    std::shared_ptr<GetMoviesUseCase> usecase) {
    this->server = server;
    this->usecase = usecase;
}

GetMoviesController::Input GetMoviesController::deserializeInput(
    const httplib::Request& req) {
    Input input;

    try {
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

std::string GetMoviesController::serializeResponse(
    const std::vector<Movie>& movies) {
    rapidjson::Document document;
    document.SetArray();

    for (const auto& movie : movies) {
        rapidjson::Value movieObject(rapidjson::kObjectType);

        rapidjson::Value idValue;
        idValue.SetString(movie.getId().c_str(), movie.getId().length(),
                          document.GetAllocator());
        movieObject.AddMember("id", idValue, document.GetAllocator());

        rapidjson::Value titleValue;
        titleValue.SetString(movie.getTitle().c_str(),
                             movie.getTitle().length(),
                             document.GetAllocator());
        movieObject.AddMember("title", titleValue, document.GetAllocator());

        rapidjson::Value imageUrlValue;
        imageUrlValue.SetString(movie.getImageUrl().c_str(),
                                movie.getImageUrl().length(),
                                document.GetAllocator());
        movieObject.AddMember("imageUrl", imageUrlValue,
                              document.GetAllocator());

        document.PushBack(movieObject, document.GetAllocator());
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

void GetMoviesController::registerRoute() {
    server->Get("/api/movies", [&](const httplib::Request& req,
                                   httplib::Response& res) {
        try {
            auto input = deserializeInput(req);
            auto response = usecase->execute(input.page, input.pageSize);
            res.set_content(serializeResponse(response), "application/json");
        } catch (AppError& error) {
            handleAppError(error, res);
        }
    });
}
