// registration_service.hpp - the heart of CampusConnect.
// It works. Every baseline test passes. Your job is to change it safely.
#pragma once

#include <string>
#include <vector>

#include "campus_admin_api.hpp"
#include "models.hpp"

namespace campus {

class RegistrationService : public CampusAdminAPI {
public:
    void addEvent(const Event& event);

    RegistrationResult registerAttendee(const Attendee& attendee,
                                        const std::string& eventId) override;

    int bookingCount(const std::string& eventId) const;
    bool isNotificationPending(const std::string& attendeeId,
                               const std::string& eventId) const;

    std::vector<EventSummary> listEvents() const override;
    bool deleteEvent(const std::string& eventId) override;
    std::string exportAttendees(const std::string& eventId) const override;

private:
    const Event* findEvent(const std::string& eventId) const;
    const Attendee* findAttendee(const std::string& attendeeId) const;

    std::vector<Event> events_;
    std::vector<Booking> bookings_;
    std::vector<Attendee> attendees_;
};

}  // namespace campus
