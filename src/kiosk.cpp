#include "kiosk.hpp"

namespace campus {

Kiosk::Kiosk(CampusAdminAPI& api) : api_(api) {}

std::string Kiosk::render() const {
    std::string screen = "CampusConnect - What's on\n";
    const auto events = api_.listEvents();
    if (events.empty()) {
        return screen + "No events today.\n";
    }
    for (const EventSummary& event : events) {
        screen += event.title + " | seats left: " + std::to_string(event.seatsLeft) + "\n";
    }
    return screen;
}

}  // namespace campus
