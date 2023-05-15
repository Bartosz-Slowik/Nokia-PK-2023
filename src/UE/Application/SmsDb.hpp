#pragma once

#include <vector>

#include "ISmsDb.hpp"
#include "Sms.hpp"

namespace ue {

enum class SmsState { NotViewed, Viewed };

class SmsDb : public ISmsDb {
 public:
  using SmsMessages = std::vector<std::pair<Sms, SmsState>>;

  void addReceivedSms(const Sms& sms) override;
  const SmsMessages& getSmsMessages() { return smsMessages; }
  void addSms(const Sms& sms) override;
  void markLastSmsSentAsFailed() override;

 private:
  SmsMessages smsMessages;
};

}  // namespace ue
