#ifndef _SEATS_COMMON_DATA_FIND_SESSION_H_
#define _SEATS_COMMON_DATA_FIND_SESSION_H_

#include <optional>
#include <string>

#include "../../../common/data/session.h"

class FindSessionRepository {
   public:
    virtual ~FindSessionRepository() {}

    virtual std::optional<DBSession> findSession(std::string &movieId,
                                                 std::string &theaterId,
                                                 std::string &sinceDate) = 0;
};

class InMemoryFindSessionRepository : public FindSessionRepository {
   private:
    std::map<std::string, DBSession> &sessions;
    bool isDateAfter(const std::string &first, const std::string &second);

   public:
    InMemoryFindSessionRepository(std::map<std::string, DBSession> &sessions)
        : sessions(sessions) {}
    virtual ~InMemoryFindSessionRepository() {}

    std::optional<DBSession> findSession(std::string &movieId,
                                         std::string &theaterId,
                                         std::string &sinceDate) override;
};

#endif
