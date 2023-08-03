#include <httplib/httplib.h>

#include <memory>
#include <mutex>

#include "common/data/movie.h"
#include "common/data/seat.h"
#include "common/data/session.h"
#include "common/data/theater.h"
#include "movies/get/presentation/controller.h"
#include "seats/book/presentation/controller.h"
#include "seats/common/data/find_session.h"
#include "seats/getAvailable/presentation/controller.h"
#include "theaters/get/presentation/controller.h"

int main() {
    auto server = std::make_shared<httplib::Server>();

    // Using manual dependency injection here, let's keep it simple for this
    // example
    std::mutex seatsLock;
    auto movies = DBMovie::Mother::buildMovies(10);
    auto theaters = DBTheater::Mother::buildTheaters(10);
    auto sessions = DBSession::Mother::buildSessions(movies, theaters, 3);
    auto seats = DBSeat::Mother::buildSeats(sessions, 20);

    auto findSessionRepository =
        std::make_shared<InMemoryFindSessionRepository>(sessions);

    auto getMoviesRepository =
        std::make_shared<InMemoryGetMoviesRepository>(movies);
    auto getMoviesUseCase =
        std::make_shared<GetMoviesUseCase>(getMoviesRepository);
    auto getMoviesController =
        std::make_shared<GetMoviesController>(server, getMoviesUseCase);

    auto getTheatersRepository =
        std::make_shared<InMemoryGetTheatersByMovieRepository>(
            theaters, sessions);
    auto getTheatersUseCase =
        std::make_shared<GetTheatersByMovieUseCase>(getTheatersRepository);
    auto getTheatersController =
        std::make_shared<GetTheatersController>(server, getTheatersUseCase);

    auto getAvailableSeatsRepository =
        std::make_shared<InMemoryGetAvailableSeatsRepository>(
            findSessionRepository, seats);
    auto getAvailableSeatsUseCase =
        std::make_shared<GetAvailableSeatsUseCase>(getAvailableSeatsRepository);
    auto getAvailableSeatsController =
        std::make_shared<GetAvailableSeatsController>(server,
                                                      getAvailableSeatsUseCase);

    auto bookSeatsRepository = std::make_shared<InMemoryBookSeatsRepository>(
        findSessionRepository, seatsLock, seats);
    auto bookSeatsUseCase =
        std::make_shared<BookSeatsUseCase>(bookSeatsRepository);
    auto bookSeatsController =
        std::make_shared<BookSeatsController>(server, bookSeatsUseCase);

    // Register the controllers
    getMoviesController->registerRoute();
    getTheatersController->registerRoute();
    getAvailableSeatsController->registerRoute();
    bookSeatsController->registerRoute();

    std::cout << "Server listening on port 8080" << std::endl << std::flush;
    server->listen("0.0.0.0", 8080);

    return 0;
}
