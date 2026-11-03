// test_rig.hpp - the ONLY place where tests know how CampusConnect is wired.
//
// RULE OF THE GAME
//   When you refactor (inject a notifier, add a formatter, narrow an interface...),
//   update the wiring HERE. Do NOT change the expected values in baseline_tests.cpp.
//   If a baseline test fails, your change broke a promise. Fix the code, not the test.
#pragma once

#include <string>

#include "email_provider.hpp"
#include "kiosk.hpp"
#include "models.hpp"
#include "registration_service.hpp"
#include "sms_gateway.hpp"

struct TestRig {
    campus::RegistrationService service;

    TestRig() {
        campus::EmailProvider::reset();
        campus::SmsGateway::reset();
    }

    // ---------- actions ----------
    void addEvent(const std::string& id, const std::string& title, int capacity) {
        service.addEvent({id, title, capacity});
    }

    campus::RegistrationResult registerAttendee(const campus::Attendee& attendee,
                                                const std::string& eventId) {
        return service.registerAttendee(attendee, eventId);
    }

    // ---------- observations ----------
    int bookingCount(const std::string& eventId) const { return service.bookingCount(eventId); }

    bool isNotificationPending(const std::string& attendeeId, const std::string& eventId) const {
        return service.isNotificationPending(attendeeId, eventId);
    }

    // Confirmations the provider ACCEPTED.
    int messagesSent() const { return static_cast<int>(campus::EmailProvider::outbox().size()); }

    // Times the system TRIED to send a confirmation (accepted or not).
    int sendAttempts() const { return campus::EmailProvider::sendAttempts(); }

    std::string lastMessageText() const {
        const auto& outbox = campus::EmailProvider::outbox();
        return outbox.empty() ? "" : outbox.back().text;
    }

    std::string kioskScreen() {
        campus::Kiosk kiosk(service);
        return kiosk.render();
    }

    // ---------- simulation switches ----------
    void simulateEmailOutage() { campus::EmailProvider::setOutage(true); }
};

// ---------- sample attendees (fictional) ----------
inline campus::Attendee ana() {
    return {"s-1001", "Ana Rojas", "ana@uni.example", "+56 9 1111 1111", "en"};
}
inline campus::Attendee benja() {
    return {"s-1002", "Benjamin Soto", "benja@uni.example", "+56 9 2222 2222", "en"};
}
inline campus::Attendee carla() {
    return {"s-1003", "Carla Diaz", "carla@uni.example", "+56 9 3333 3333", "es"};
}
