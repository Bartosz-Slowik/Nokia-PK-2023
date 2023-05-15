#pragma once

#include "IUeGui.hpp"

namespace ue {

class IUserEventsHandler {
 public:
  virtual ~IUserEventsHandler() = default;
  virtual void handleSendCallDrop(common::PhoneNumber) = 0;
  virtual void handleSendCallRequest(common::PhoneNumber) = 0;
  virtual void handleSendCallAccept(common::PhoneNumber) = 0;
};

class IUserPort {
 public:
  virtual ~IUserPort() = default;

  virtual void showNotConnected() = 0;
  virtual void showConnecting() = 0;
  virtual void showConnected() = 0;
  virtual IUeGui::ISmsComposeMode& composeSms() = 0;
  virtual void showNewSmsNotification() = 0;
  virtual int getAction() = 0;
  virtual void acceptCallback(IUeGui::Callback acceptCallback) = 0;
  virtual void rejectCallback(IUeGui::Callback rejectCallback) = 0;
  virtual void showEnterPhoneNumber() = 0;
  virtual void showDialing(common::PhoneNumber) = 0;
  virtual void callAchieved(common::PhoneNumber) = 0;
  virtual void showPartnerNotAvailable(common::PhoneNumber) = 0;
};

}  // namespace ue
