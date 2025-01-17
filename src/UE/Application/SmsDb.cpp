#include <memory>

#include "SmsDb.hpp"

namespace ue {

void SmsDb::addReceivedSms(const Sms& sms) {
  smsMessages.insert(smsMessages.begin(),
                     std::make_pair(sms, SmsState::NotViewed));
}

void SmsDb::addSentSms(const Sms& sms) {
  smsMessages.insert(smsMessages.begin(),
                     std::make_pair(sms, SmsState::Viewed));
}

void ue::SmsDb::markLastSmsSentAsFailed() {
  if (!smsMessages.empty()) {
    smsMessages.back().first.markAsNotReceived();
  }
}

std::unique_ptr<Sms> SmsDb::retrieveSms(size_t index) {
  if (index < smsMessages.size()) {
    markAsViewed(index);
    return std::make_unique<Sms>(smsMessages.at(index).first);
  } else {
    return nullptr;
  }
}

void SmsDb::markAsViewed(size_t index) {
  smsMessages.at(index).second = SmsState::Viewed;
}

bool SmsDb::isUnreadSms() {
  for (const auto& sms : smsMessages) {
    if (sms.second == SmsState::NotViewed) {
      return true;
    }
  }
  return false;
}

}  // namespace ue
