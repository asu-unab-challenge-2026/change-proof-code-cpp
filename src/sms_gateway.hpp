// sms_gateway.hpp - a SIMULATED SMS vendor SDK, bought by Campus IT.
// It is already in the repo but nothing uses it yet.
// Note: its API is different from EmailProvider's (it returns a status code).
#pragma once

#include <string>
#include <vector>

namespace campus {

struct SentSms {
    std::string phone;
    std::string body;
};

class SmsGateway {
public:
    static constexpr int kAccepted = 0;       // vendor accepted the text
    static constexpr int kInvalidNumber = 21; // vendor rejected the phone number

    // Returns kAccepted (0) if the vendor accepted the text; any other value means rejected.
    int sendText(const std::string& phoneNumber, const std::string& body);

    // ---- simulation controls (shared by every SmsGateway object) ----
    static const std::vector<SentSms>& outbox();
    static int sendAttempts();
    static void reset();

private:
    static std::vector<SentSms> outbox_;
    static int attempts_;
};

}  // namespace campus
