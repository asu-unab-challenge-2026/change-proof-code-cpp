#include "registration_service.hpp"

#include <algorithm>

#include "email_provider.hpp"

namespace campus {

void RegistrationService::addEvent(const Event& event) { events_.push_back(event); }

RegistrationResult RegistrationService::registerAttendee(const Attendee& attendee,
                                                         const std::string& eventId) {
    // Look up the event.
    const Event* event = findEvent(eventId);
    if (event == nullptr) {
        return RegistrationResult::Rejected;
    }

    // One seat per attendee per event.
    for (const Booking& booking : bookings_) {
        if (booking.attendeeId == attendee.id && booking.eventId == eventId) {
            return RegistrationResult::Duplicate;
        }
    }

    // No overbooking.
    if (bookingCount(eventId) >= event->capacity) {
        return RegistrationResult::Rejected;
    }

    // Save the booking. The confirmation is pending until a provider accepts it.
    bookings_.push_back({attendee.id, eventId, true});
    if (findAttendee(attendee.id) == nullptr) {
        attendees_.push_back(attendee);
    }

    // Write the confirmation.
    std::string text = "You are booked for " + event->title + ".";

    // Send it.
    EmailProvider provider;
    bool accepted = provider.send(attendee.email, text);

    if (accepted) {
        bookings_.back().notificationPending = false;
        return RegistrationResult::Booked;
    }
    return RegistrationResult::BookedNotificationPending;
}

int RegistrationService::bookingCount(const std::string& eventId) const {
    return static_cast<int>(std::count_if(
        bookings_.begin(), bookings_.end(),
        [&](const Booking& booking) { return booking.eventId == eventId; }));
}

bool RegistrationService::isNotificationPending(const std::string& attendeeId,
                                                const std::string& eventId) const {
    for (const Booking& booking : bookings_) {
        if (booking.attendeeId == attendeeId && booking.eventId == eventId) {
            return booking.notificationPending;
        }
    }
    return false;  // no booking, so nothing is pending
}

std::vector<EventSummary> RegistrationService::listEvents() const {
    std::vector<EventSummary> summaries;
    for (const Event& event : events_) {
        summaries.push_back({event.id, event.title, event.capacity - bookingCount(event.id)});
    }
    return summaries;
}

bool RegistrationService::deleteEvent(const std::string& eventId) {
    auto it = std::find_if(events_.begin(), events_.end(),
                           [&](const Event& event) { return event.id == eventId; });
    if (it == events_.end()) {
        return false;
    }
    events_.erase(it);
    bookings_.erase(std::remove_if(bookings_.begin(), bookings_.end(),
                                   [&](const Booking& booking) { return booking.eventId == eventId; }),
                    bookings_.end());
    return true;
}

std::string RegistrationService::exportAttendees(const std::string& eventId) const {
    std::string csv = "id,name,email\n";
    for (const Booking& booking : bookings_) {
        if (booking.eventId != eventId) {
            continue;
        }
        if (const Attendee* attendee = findAttendee(booking.attendeeId)) {
            csv += attendee->id + "," + attendee->name + "," + attendee->email + "\n";
        }
    }
    return csv;
}

const Event* RegistrationService::findEvent(const std::string& eventId) const {
    for (const Event& event : events_) {
        if (event.id == eventId) {
            return &event;
        }
    }
    return nullptr;
}

const Attendee* RegistrationService::findAttendee(const std::string& attendeeId) const {
    for (const Attendee& attendee : attendees_) {
        if (attendee.id == attendeeId) {
            return &attendee;
        }
    }
    return nullptr;
}

}  // namespace campus
