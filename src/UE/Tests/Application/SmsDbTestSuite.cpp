#include <gtest/gtest.h>

#include "Messages/PhoneNumber.hpp"
#include "SmsDb.hpp"

namespace ue {

using namespace ::testing;

class SmsDbTestSuite : public Test {
 protected:
  const common::PhoneNumber PHONE_NUMBER{112};

  SmsDb objectUnderTest;
};

TEST_F(SmsDbTestSuite, shallAddReceivedSms) {
  const Sms sms{"TEST 101010 lol", PHONE_NUMBER, PHONE_NUMBER};
  objectUnderTest.addReceivedSms(sms);

  const auto& messages = objectUnderTest.getSmsMessages();
  auto [_, smsState] = messages[0];
  ASSERT_EQ(smsState, SmsState::NotViewed);
}

}  // namespace ue
