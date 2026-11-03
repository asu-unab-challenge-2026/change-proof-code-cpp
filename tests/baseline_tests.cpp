// baseline_tests.cpp - promises CampusConnect already keeps.
//
// These 7 tests pass on the starter code. They must STILL pass after your change.
// You may change how the system is wired (in test_rig.hpp).
// You may NOT change what these tests expect (the "Then" lines).
#include <string>

#include "mini_test.hpp"
#include "test_rig.hpp"

using campus::RegistrationResult;

TEST_CASE(books_an_available_seat_and_sends_one_confirmation) {
    // Given an event with 2 seats
    TestRig rig;
    rig.addEvent("robotics-night", "Robotics Night", 2);
    // When Ana registers
    RegistrationResult result = rig.registerAttendee(ana(), "robotics-night");
    // Then she holds one seat and one confirmation was accepted
    CHECK_EQ(result, RegistrationResult::Booked);
    CHECK_EQ(rig.bookingCount("robotics-night"), 1);
    CHECK_EQ(rig.messagesSent(), 1);
}

TEST_CASE(confirmation_text_names_the_event) {
    // Given an event
    TestRig rig;
    rig.addEvent("robotics-night", "Robotics Night", 2);
    // When an English-speaking attendee registers
    rig.registerAttendee(ana(), "robotics-night");
    // Then the confirmation names the event
    CHECK_EQ(rig.lastMessageText(), std::string("You are booked for Robotics Night."));
}

TEST_CASE(full_event_rejects_and_sends_nothing) {
    // Given an event with 1 seat that Ana already holds
    TestRig rig;
    rig.addEvent("robotics-night", "Robotics Night", 1);
    rig.registerAttendee(ana(), "robotics-night");
    // When Benja tries to register
    RegistrationResult result = rig.registerAttendee(benja(), "robotics-night");
    // Then he is rejected, no new seat is taken, and nothing more is sent
    CHECK_EQ(result, RegistrationResult::Rejected);
    CHECK_EQ(rig.bookingCount("robotics-night"), 1);
    CHECK_EQ(rig.sendAttempts(), 1);  // only Ana's confirmation
}

TEST_CASE(unknown_event_rejects_and_sends_nothing) {
    // Given no event called "chess-club"
    TestRig rig;
    rig.addEvent("robotics-night", "Robotics Night", 2);
    // When Ana registers for it
    RegistrationResult result = rig.registerAttendee(ana(), "chess-club");
    // Then she is rejected and nothing is sent
    CHECK_EQ(result, RegistrationResult::Rejected);
    CHECK_EQ(rig.bookingCount("chess-club"), 0);
    CHECK_EQ(rig.sendAttempts(), 0);
}

TEST_CASE(duplicate_registration_keeps_one_booking) {
    // Given Ana already holds a seat
    TestRig rig;
    rig.addEvent("robotics-night", "Robotics Night", 5);
    rig.registerAttendee(ana(), "robotics-night");
    // When she registers again
    RegistrationResult result = rig.registerAttendee(ana(), "robotics-night");
    // Then she still holds exactly one seat and gets no second confirmation
    CHECK_EQ(result, RegistrationResult::Duplicate);
    CHECK_EQ(rig.bookingCount("robotics-night"), 1);
    CHECK_EQ(rig.messagesSent(), 1);
}

TEST_CASE(accepted_confirmation_clears_pending_flag) {
    // Given an event
    TestRig rig;
    rig.addEvent("robotics-night", "Robotics Night", 2);
    // When Ana is booked and the provider accepts her confirmation
    rig.registerAttendee(ana(), "robotics-night");
    // Then nothing is pending for her
    CHECK(!rig.isNotificationPending("s-1001", "robotics-night"));
}

TEST_CASE(kiosk_lists_events_with_seats_left) {
    // Given two events and one booking
    TestRig rig;
    rig.addEvent("robotics-night", "Robotics Night", 2);
    rig.addEvent("career-fair", "Career Fair", 100);
    rig.registerAttendee(ana(), "robotics-night");
    // When the lobby kiosk renders
    std::string screen = rig.kioskScreen();
    // Then both events appear with the right number of free seats
    CHECK(screen.find("Robotics Night | seats left: 1") != std::string::npos);
    CHECK(screen.find("Career Fair | seats left: 100") != std::string::npos);
}
