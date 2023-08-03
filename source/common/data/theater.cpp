#include "theater.h"

std::map<std::string, DBTheater> DBTheater::Mother::buildTheaters(uint32_t size) {
    std::map<std::string, DBTheater> theaters;

    for (uint32_t i = 1; i <= size; ++i) {
        DBTheater theater(std::to_string(i), "Theater " + std::to_string(i));

        theaters.emplace(theater.getId(), theater);
    }

    return theaters;
}
