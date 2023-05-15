#pragma once

#include <gmock/gmock.h>

#include "ISmsDb.hpp"

namespace ue {

class ISmsDbMock : public ISmsDb {
 public:
  ISmsDbMock() = default;
  ~ISmsDbMock() override = default;

  MOCK_METHOD(void, addReceivedSms, (const Sms&), (final));
  MOCK_METHOD(void, addSms, (const Sms&), (final));
  MOCK_METHOD(void, markAsViewed, (size_t index), (final));
  MOCK_METHOD(void, markLastSmsSentAsFailed, (), (final));
  MOCK_METHOD(std::unique_ptr<Sms>, retrieveSms, (size_t), (final));
  MOCK_METHOD(bool, isUnreadSms, (), (final));
};

}  // namespace ue
