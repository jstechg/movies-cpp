#ifndef _MOVIES_GET_MOVIE_H_
#define _MOVIES_GET_MOVIE_H_

#include <string>

/**
 * @class Movie
 * @brief Represents a movie entity with its details.
 * 
 * This class encapsulates the information associated with a movie, including its ID,
 * title, and an image URL. It provides methods to access these attributes.
 */
class Movie {
   private:
    std::string id;
    std::string title;
    std::string imageUrl;

   public:
    Movie(const std::string& id, const std::string& title,
          const std::string& imageUrl)
        : id(id), title(title), imageUrl(imageUrl) {}

    std::string getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getImageUrl() const { return imageUrl; }
};

#endif
