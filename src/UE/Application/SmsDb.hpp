#pragma once

#include <optional>
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
  std::unique_ptr<Sms> retrieveSms(size_t index) override;
  void addSms(const Sms& sms) override;
  void markAsViewed(size_t index) override;
  void markLastSmsSentAsFailed() override;
  bool isUnreadSms() override;

 private:
  SmsMessages smsMessages;
};

}  // namespace ue
