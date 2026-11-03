// email_provider.hpp - a SIMULATED email vendor SDK.
// No real email is sent. Accepted messages are kept in a process-wide
// outbox so that the demo and the tests can see what "would" be sent.
#pragma once

#include <string>
#include <vector>

namespace campus {

struct SentEmail {
    std::string to;
    std::string text;
};

class EmailProvider {
public:
    // Hands a message to the email vendor.
    // Returns true if the vendor accepted the message for delivery.
    // (Accepted does not mean the person has read it.)
    bool send(const std::string& toAddress, const std::string& text);

    // ---- simulation controls (shared by every EmailProvider object) ----
    static const std::vector<SentEmail>& outbox();  // messages accepted so far
    static int sendAttempts();                      // calls to send() so far
    static void setOutage(bool isDown);             // pretend the vendor is down
    static void reset();                            // clear outbox, attempts, outage

private:
    static std::vector<SentEmail> outbox_;
    static int attempts_;
    static bool outage_;
};

}  // namespace campus
