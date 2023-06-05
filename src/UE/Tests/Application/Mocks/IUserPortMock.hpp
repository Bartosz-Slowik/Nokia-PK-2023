#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue {

class IUserEventsHandlerMock : public IUserEventsHandler {
 public:
  IUserEventsHandlerMock();
  ~IUserEventsHandlerMock() override;
  MOCK_METHOD(void, handleSendCallRequest, (common::PhoneNumber), (final));
  MOCK_METHOD(void, handleSendCallDrop, (common::PhoneNumber), (final));
  MOCK_METHOD(void, handleSendCallAccept, (common::PhoneNumber), (final));
  MOCK_METHOD(void,
              handleSendCallTalk,
              (common::PhoneNumber, std::string),
              (final));
  MOCK_METHOD(void, handleStartDial, (), (final));
};

class IUserPortMock : public IUserPort {
 public:
  IUserPortMock();
  ~IUserPortMock() override;

  MOCK_METHOD(void, showNotConnected, (), (final));
  MOCK_METHOD(void, showConnecting, (), (final));
  MOCK_METHOD(void, showConnected, (), (final));
  MOCK_METHOD(void, showNewSmsNotification, (), (final));
  MOCK_METHOD(void, showSms, (size_t), (final));
  MOCK_METHOD(void, showSmsList, (), (final));
  MOCK_METHOD(SmsDb&, getSmsDb, (), (final));
  MOCK_METHOD(IUeGui::ISmsComposeMode&, composeSms, (), (final));
  MOCK_METHOD(int, getAction, (), (final));
  MOCK_METHOD(void, acceptCallback, (IUeGui::Callback), (final));
  MOCK_METHOD(void, rejectCallback, (IUeGui::Callback), (final));
  MOCK_METHOD(void, showEnterPhoneNumber, (), (final));
  MOCK_METHOD(void, showCallRequest, (common::PhoneNumber from), (final));
  MOCK_METHOD(void, showTalking, (common::PhoneNumber), (final));
  MOCK_METHOD(void, showDialing, (common::PhoneNumber phoneNumber), (final));
  MOCK_METHOD(void,
              showCallAchieved,
              (common::PhoneNumber phoneNumber),
              (final));
  MOCK_METHOD(void,
              showPartnerNotAvailable,
              (common::PhoneNumber phoneNumber),
              (final));
  MOCK_METHOD(void,
              showNewCallTalk,
              (common::PhoneNumber, std::string),
              (final));
};

}  // namespace ue
