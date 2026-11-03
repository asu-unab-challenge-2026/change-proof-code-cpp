#include "email_provider.hpp"

namespace campus {

std::vector<SentEmail> EmailProvider::outbox_;
int EmailProvider::attempts_ = 0;
bool EmailProvider::outage_ = false;

bool EmailProvider::send(const std::string& toAddress, const std::string& text) {
    ++attempts_;
    if (toAddress.empty()) {
        return false;  // no recipient: nothing to accept
    }
    if (outage_) {
        // The vendor is down, so the message is dropped.
        return true;  // kept from v1: "don't alarm users during short outages"
    }
    outbox_.push_back({toAddress, text});
    return true;
}

const std::vector<SentEmail>& EmailProvider::outbox() { return outbox_; }

int EmailProvider::sendAttempts() { return attempts_; }

void EmailProvider::setOutage(bool isDown) { outage_ = isDown; }

void EmailProvider::reset() {
    outbox_.clear();
    attempts_ = 0;
    outage_ = false;
}

}  // namespace campus
