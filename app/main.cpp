// main.cpp - a short demo run of CampusConnect.
// Build and run:  g++ -std=c++17 -Isrc src/*.cpp app/main.cpp -o campus_demo && ./campus_demo
#include <iostream>

#include "email_provider.hpp"
#include "kiosk.hpp"
#include "registration_service.hpp"

using namespace campus;

int main() {
    EmailProvider::reset();  // start with an empty simulated outbox
    RegistrationService service;
    service.addEvent({"robotics-night", "Robotics Night", 2});
    service.addEvent({"career-fair", "Career Fair", 100});

    Attendee ana{"s-1001", "Ana Rojas", "ana@uni.example", "+56 9 1111 1111", "en"};
    Attendee benja{"s-1002", "Benjamin Soto", "benja@uni.example", "+56 9 2222 2222", "en"};
    Attendee carla{"s-1003", "Carla Diaz", "carla@uni.example", "+56 9 3333 3333", "es"};

    std::cout << "Ana   -> Robotics Night : " << service.registerAttendee(ana, "robotics-night") << "\n";
    std::cout << "Ana   -> Robotics Night : " << service.registerAttendee(ana, "robotics-night") << "\n";
    std::cout << "Benja -> Robotics Night : " << service.registerAttendee(benja, "robotics-night") << "\n";
    std::cout << "Carla -> Robotics Night : " << service.registerAttendee(carla, "robotics-night") << "\n";
    std::cout << "Carla -> Chess Club     : " << service.registerAttendee(carla, "chess-club") << "\n";

    std::cout << "\nEmails accepted by the provider:\n";
    for (const SentEmail& email : EmailProvider::outbox()) {
        std::cout << "  to " << email.to << ": " << email.text << "\n";
    }

    Kiosk kiosk(service);
    std::cout << "\n" << kiosk.render();
    return 0;
}
