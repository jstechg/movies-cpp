#ifndef _COMMON_DATA_MOVIE_H_
#define _COMMON_DATA_MOVIE_H_

#include <string>
#include <map>

class DBMovie {
private:
    std::string id;
    std::string title;
    std::string imageUrl;

public:
    DBMovie(const std::string& id, const std::string& title, const std::string& imageUrl)
        : id(id), title(title), imageUrl(imageUrl) {}

    std::string getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getImageUrl() const { return imageUrl; }

    void setId(const std::string& id) { this->id = id; }
    void setTitle(const std::string& title) { this->title = title; }
    void setImageUrl(const std::string& imageUrl) { this->imageUrl = imageUrl; }

    static std::map<std::string, DBMovie> MOCK_MOVIES;

    class Mother {
        public:
            static std::map<std::string, DBMovie> buildMovies(uint32_t size);
    };
};

#endif
