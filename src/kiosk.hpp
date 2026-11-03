// kiosk.hpp - the public screen in the library lobby.
// Anyone walking past can use it. It only shows what's on.
#pragma once

#include <string>

#include "campus_admin_api.hpp"

namespace campus {

class Kiosk {
public:
    explicit Kiosk(CampusAdminAPI& api);

    // One line per event, e.g. "Robotics Night | seats left: 2"
    std::string render() const;

private:
    CampusAdminAPI& api_;
};

}  // namespace campus
