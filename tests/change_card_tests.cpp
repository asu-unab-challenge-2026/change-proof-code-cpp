// change_card_tests.cpp - YOUR tests for YOUR change card.
//
// Write at least 2 tests, ideally 3:
//   1. a success case for the NEW behavior on your card
//   2. a failure or boundary case (full event, outage, missing phone number...)
//   3. a check that an OLD promise still holds after your change
//
// Name each test after the behavior it proves, e.g.
//   TEST_CASE(spanish_attendee_gets_spanish_confirmation)
// Use Given / When / Then comments, like baseline_tests.cpp.
//
// Need a different wiring for one test (a fake, an SMS channel...)?
// Build it right inside the test, or add a helper to test_rig.hpp.
#include <string>

#include "mini_test.hpp"
#include "test_rig.hpp"

using campus::RegistrationResult;

// Example of the shape. Rename it, change it, or delete it.
TEST_CASE(example_two_attendees_take_two_seats) {
    // Given an event with plenty of seats
    TestRig rig;
    rig.addEvent("career-fair", "Career Fair", 100);
    // When two different attendees register
    rig.registerAttendee(ana(), "career-fair");
    rig.registerAttendee(benja(), "career-fair");
    // Then two seats are taken
    CHECK_EQ(rig.bookingCount("career-fair"), 2);
}
