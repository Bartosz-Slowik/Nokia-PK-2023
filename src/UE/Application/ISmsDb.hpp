#pragma once

#include "Messages/PhoneNumber.hpp"
#include "Sms.hpp"

namespace ue {

class ISmsDb {
 public:
  virtual ~ISmsDb() = default;

  virtual void addReceivedSms(const Sms& sms) = 0;
  virtual void addSms(const Sms& sms) = 0;
  virtual void markLastSmsSentAsFailed() = 0;
};

}  // namespace ue
