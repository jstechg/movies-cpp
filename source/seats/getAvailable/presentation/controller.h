#ifndef _SEATS_GET_CONTROLLER_H_
#define _SEATS_GET_CONTROLLER_H_

#include <httplib/httplib.h>
#include <memory>
#include <string>

#include "../logic/usecase.h"

class GetAvailableSeatsController {
   private:
    std::shared_ptr<httplib::Server> server;
    std::shared_ptr<GetAvailableSeatsUseCase> usecase;

    struct Input {
        std::string movieId;
        std::string theaterId;
        std::string sinceDate;
    };

    Input deserializeInput(const httplib::Request& req);
    std::string serializeResponse(
        const std::vector<std::string> &seats);

   public:
    GetAvailableSeatsController(std::shared_ptr<httplib::Server> server, std::shared_ptr<GetAvailableSeatsUseCase> usecase);
    virtual ~GetAvailableSeatsController() {}

    void registerRoute();
};

#endif
