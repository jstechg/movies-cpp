#ifndef _THEATERS_GET_CONTROLLER_H_
#define _THEATERS_GET_CONTROLLER_H_

#include <httplib/httplib.h>
#include <memory>

#include "../logic/usecase.h"

class GetTheatersController {
   private:
    std::shared_ptr<httplib::Server> server;
    std::shared_ptr<GetTheatersByMovieUseCase> usecase;

    struct Input {
        std::string movieId;
        uint32_t page;
        uint32_t pageSize;
    };

    Input deserializeInput(const httplib::Request& req);
    std::string serializeResponse(
        const std::vector<Theater> &theaters);

   public:
    GetTheatersController(std::shared_ptr<httplib::Server> server, std::shared_ptr<GetTheatersByMovieUseCase> usecase);
    virtual ~GetTheatersController() {}

    void registerRoute();
};

#endif
