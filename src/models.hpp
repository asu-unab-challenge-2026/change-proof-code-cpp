// models.hpp - the plain data types used by CampusConnect.
// Fictional teaching system. No real people, emails or phone numbers.
#pragma once

#include <ostream>
#include <string>

namespace campus {

struct Attendee {
    std::string id;               // e.g. "s-1001"
    std::string name;             // e.g. "Ana Rojas"
    std::string email;            // e.g. "ana@uni.example"
    std::string phone;            // e.g. "+56 9 1111 1111"
    std::string language = "en";  // preferred language code
};

struct Event {
    std::string id;     // e.g. "robotics-night"
    std::string title;  // e.g. "Robotics Night"
    int capacity = 0;   // number of seats
};

struct Booking {
    std::string attendeeId;
    std::string eventId;
    bool notificationPending = true;  // true until a provider accepts the confirmation
};

struct EventSummary {
    std::string id;
    std::string title;
    int seatsLeft = 0;
};

enum class RegistrationResult {
    Booked,                     // seat booked AND the confirmation was accepted by the provider
    BookedNotificationPending,  // seat booked, but the confirmation was NOT accepted (yet)
    Duplicate,                  // this attendee already holds a seat at this event
    Rejected                    // unknown event, or no seats left
};

inline const char* toString(RegistrationResult result) {
    switch (result) {
        case RegistrationResult::Booked: return "Booked";
        case RegistrationResult::BookedNotificationPending: return "BookedNotificationPending";
        case RegistrationResult::Duplicate: return "Duplicate";
        case RegistrationResult::Rejected: return "Rejected";
    }
    return "Unknown";
}

inline std::ostream& operator<<(std::ostream& out, RegistrationResult result) {
    return out << toString(result);
}

}  // namespace campus
