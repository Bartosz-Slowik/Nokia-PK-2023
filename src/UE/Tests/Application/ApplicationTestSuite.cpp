#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include "Application.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"

namespace ue {
using namespace ::testing;

class ApplicationTestSuite : public Test {
 protected:
  const common::PhoneNumber PHONE_NUMBER{112};
  const common::BtsId BTS_ID{211};
  NiceMock<common::ILoggerMock> loggerMock;
  StrictMock<IBtsPortMock> btsPortMock;
  StrictMock<IUserPortMock> userPortMock;
  StrictMock<ITimerPortMock> timerPortMock;

  Expectation expectNotConnectedOnStart =
      EXPECT_CALL(userPortMock, showNotConnected());

  Application objectUnderTest{PHONE_NUMBER, loggerMock, btsPortMock,
                              userPortMock, timerPortMock};
};

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite {
  void sendAttachRequestOnSib();
};

void ApplicationNotConnectedTestSuite::sendAttachRequestOnSib() {
  using namespace std::chrono_literals;
  EXPECT_CALL(btsPortMock, sendAttachRequest(BTS_ID));
  EXPECT_CALL(userPortMock, showConnecting());
  EXPECT_CALL(timerPortMock, startTimer(1000ms));
  objectUnderTest.handleSib(BTS_ID);
}

TEST_F(ApplicationNotConnectedTestSuite, shallSendAttachRequestOnSib) {
  sendAttachRequestOnSib();
}

struct ApplicationConnectingTestSuite : ApplicationNotConnectedTestSuite {
  ApplicationConnectingTestSuite();
};

ApplicationConnectingTestSuite::ApplicationConnectingTestSuite() {
  sendAttachRequestOnSib();
}

TEST_F(ApplicationConnectingTestSuite, shallConnectOnAttachAccept) {
  EXPECT_CALL(userPortMock, showConnected());
  EXPECT_CALL(timerPortMock, stopTimer());
  objectUnderTest.handleAttachAccept();
}

TEST_F(ApplicationConnectingTestSuite, shallNotConnectOnAttachReject) {
  EXPECT_CALL(userPortMock, showNotConnected());
  EXPECT_CALL(timerPortMock, stopTimer());
  objectUnderTest.handleAttachReject();
}

TEST_F(ApplicationConnectingTestSuite, shallNotConnectOnTimeout) {
  EXPECT_CALL(userPortMock, showNotConnected());
  objectUnderTest.handleTimeout();
}

struct ApplicationConnectedTestSuite : ApplicationConnectingTestSuite {
  ApplicationConnectedTestSuite();
  void makeConnected();
};
ApplicationConnectedTestSuite::ApplicationConnectedTestSuite() {
  makeConnected();
}

void ApplicationConnectedTestSuite::makeConnected() {
  EXPECT_CALL(userPortMock, showConnected());
  EXPECT_CALL(timerPortMock, stopTimer());
  objectUnderTest.handleAttachAccept();
}

TEST_F(ApplicationConnectedTestSuite,
       shallShowNotConnectedOnDisconnectFromBts) {
  EXPECT_CALL(userPortMock, showNotConnected());
  objectUnderTest.handleDisconnected();
}
TEST_F(ApplicationConnectedTestSuite, shallReattach) {
  EXPECT_CALL(userPortMock, showNotConnected());
  objectUnderTest.handleDisconnected();
  sendAttachRequestOnSib();
  makeConnected();
}

}  // namespace ue
