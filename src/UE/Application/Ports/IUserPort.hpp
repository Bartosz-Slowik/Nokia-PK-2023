#pragma once

#include "IUeGui.hpp"
#include "SmsDb.hpp"

namespace ue {

class IUserEventsHandler {
 public:
  virtual ~IUserEventsHandler() = default;

  virtual void handleSendCallRequest(common::PhoneNumber) = 0;
  virtual void handleSendCallAccept(common::PhoneNumber) = 0;
  virtual void handleSendCallTalk(common::PhoneNumber, std::string) = 0;
  virtual void handleSendCallDrop(common::PhoneNumber) = 0;
  virtual void handleStartDial() = 0;
};

class IUserPort {
 public:
  virtual ~IUserPort() = default;

  virtual void showNotConnected() = 0;
  virtual void showConnecting() = 0;
  virtual void showConnected() = 0;
  virtual IUeGui::ISmsComposeMode& composeSms() = 0;
  virtual void showNewSmsNotification() = 0;
  virtual void showSmsList() = 0;
  virtual void showSms(size_t index) = 0;
  virtual SmsDb& getSmsDb() = 0;
  virtual int getAction() = 0;
  virtual void acceptCallback(IUeGui::Callback acceptCallback) = 0;
  virtual void rejectCallback(IUeGui::Callback rejectCallback) = 0;
  virtual void showEnterPhoneNumber() = 0;
  virtual void showDialing(common::PhoneNumber) = 0;
  virtual void showCallAchieved(common::PhoneNumber) = 0;
  virtual void showPartnerNotAvailable(common::PhoneNumber) = 0;
  virtual void showCallRequest(common::PhoneNumber from) = 0;
  virtual void showTalking(common::PhoneNumber) = 0;
  virtual void showNewCallTalk(common::PhoneNumber, std::string) = 0;
};

}  // namespace ue
