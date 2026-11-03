// campus_admin_api.hpp - everything the campus admin tool can do.
// In C++, a class made only of pure virtual functions ("= 0") plays the
// role of an interface: it is a promise that implementations must keep.
#pragma once

#include <string>
#include <vector>

#include "models.hpp"

namespace campus {

class CampusAdminAPI {
public:
    virtual ~CampusAdminAPI() = default;

    // Every event with the number of seats still free.
    virtual std::vector<EventSummary> listEvents() const = 0;

    // Books one seat for the attendee and sends a confirmation.
    virtual RegistrationResult registerAttendee(const Attendee& attendee,
                                                const std::string& eventId) = 0;

    // Removes the event and all of its bookings. Returns false if unknown.
    virtual bool deleteEvent(const std::string& eventId) = 0;

    // CSV with one line per attendee: id,name,email  (personal data!)
    virtual std::string exportAttendees(const std::string& eventId) const = 0;
};

}  // namespace campus
