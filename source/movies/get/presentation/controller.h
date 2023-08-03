#ifndef _MOVIES_GET_CONTROLLER_H_
#define _MOVIES_GET_CONTROLLER_H_

#include <httplib/httplib.h>
#include <memory>

#include "../logic/usecase.h"

class GetMoviesController {
   private:
    std::shared_ptr<httplib::Server> server;
    std::shared_ptr<GetMoviesUseCase> usecase;

    struct Input {
        uint32_t page;
        uint32_t pageSize;
    };

    Input deserializeInput(const httplib::Request& req);
    std::string serializeResponse(
        const std::vector<Movie> &movies);

   public:
    GetMoviesController(std::shared_ptr<httplib::Server> server, std::shared_ptr<GetMoviesUseCase> usecase);
    virtual ~GetMoviesController() {}

    void registerRoute();
};

#endif
