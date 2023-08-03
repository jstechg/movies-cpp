#ifndef _COMMON_DATA_THEATER_H_
#define _COMMON_DATA_THEATER_H_

#include <map>
#include <string>

class DBTheater {
   private:
    std::string id;
    std::string name;

   public:
    DBTheater(const std::string& id, const std::string& name)
        : id(id), name(name) {}

    std::string getId() const { return id; }
    std::string getName() const { return name; }

    void setId(const std::string& id) { this->id = id; }
    void setName(const std::string& name) { this->name = name; }

    class Mother {
       public:
        static std::map<std::string, DBTheater> buildTheaters(uint32_t size);
    };
};

#endif
