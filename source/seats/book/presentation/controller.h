#ifndef _SEATS_BOOK_CONTROLLER_H_
#define _SEATS_BOOK_CONTROLLER_H_

#include <httplib/httplib.h>
#include <memory>
#include <string>

#include "../logic/usecase.h"

class BookSeatsController {
   private:
    std::shared_ptr<httplib::Server> server;
    std::shared_ptr<BookSeatsUseCase> usecase;

    struct Input {
        std::string movieId;
        std::string theaterId;
        std::string sinceDate;
        std::vector<std::string> seats;
    };

    Input deserializeInput(const httplib::Request& req);

   public:
    BookSeatsController(std::shared_ptr<httplib::Server> server, std::shared_ptr<BookSeatsUseCase> usecase);
    virtual ~BookSeatsController() {}

    void registerRoute();
};

#endif
