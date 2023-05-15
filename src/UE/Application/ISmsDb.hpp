#pragma once

#include <memory>

#include "Messages/PhoneNumber.hpp"
#include "Sms.hpp"

namespace ue {

class ISmsDb {
 public:
  virtual ~ISmsDb() = default;

  virtual void addReceivedSms(const Sms& sms) = 0;
  virtual void addSms(const Sms& sms) = 0;
  virtual std::unique_ptr<Sms> retrieveSms(size_t index) = 0;
  virtual void markAsViewed(size_t index) = 0;
  virtual void markLastSmsSentAsFailed() = 0;
  virtual bool isUnreadSms() = 0;
};

}  // namespace ue
