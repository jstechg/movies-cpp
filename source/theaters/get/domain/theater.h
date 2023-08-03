#ifndef _THEATER_GET_THEATERS_H_
#define _THEATER_GET_THEATERS_H_

#include <string>

/**
 * @class Theater
 * @brief Represents a theater entity with its details.
 * 
 * This class encapsulates the information associated with a theater, including its
 * ID and name. It provides methods to access these attributes.
 */
class Theater {
private:
    std::string id;
    std::string name;

public:
    Theater(const std::string& id, const std::string& name)
        : id(id), name(name) {}

    std::string getId() const { return id; }
    std::string getName() const { return name; }
};

#endif
