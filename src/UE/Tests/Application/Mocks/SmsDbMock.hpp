#pragma once

#include <gmock/gmock.h>

#include "SmsDb.hpp"

namespace ue {

class SmsDbMock : public SmsDb {
 public:
  SmsDbMock() = default;
  ~SmsDbMock() override = default;

  MOCK_METHOD(void, addReceivedSms, (const Sms&), (final));
  MOCK_METHOD(void, addSentSms, (const Sms&), (final));
};

}  // namespace ue
