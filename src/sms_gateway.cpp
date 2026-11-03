#include "sms_gateway.hpp"

namespace campus {

std::vector<SentSms> SmsGateway::outbox_;
int SmsGateway::attempts_ = 0;

int SmsGateway::sendText(const std::string& phoneNumber, const std::string& body) {
    ++attempts_;
    if (phoneNumber.empty()) {
        return kInvalidNumber;
    }
    outbox_.push_back({phoneNumber, body});
    return kAccepted;
}

const std::vector<SentSms>& SmsGateway::outbox() { return outbox_; }

int SmsGateway::sendAttempts() { return attempts_; }

void SmsGateway::reset() {
    outbox_.clear();
    attempts_ = 0;
}

}  // namespace campus
