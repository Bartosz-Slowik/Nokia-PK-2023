#pragma once

#include "IUeGui.hpp"
#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"

namespace {
int NO_ACTION = -1;
}

namespace ue {

class UserPort : public IUserPort {
 public:
  UserPort(common::ILogger& logger,
           IUeGui& gui,
           common::PhoneNumber phoneNumber);
  void start(IUserEventsHandler& handler);
  void stop();

  void showNotConnected() override;
  void showConnecting() override;
  void showConnected() override;
  void showNewSmsNotification() override;
  IUeGui::ISmsComposeMode& composeSms() override;
  int getAction() override;
  void acceptCallback(IUeGui::Callback acceptCallback) override;
  void rejectCallback(IUeGui::Callback rejectCallback) override;
  void showEnterPhoneNumber() override;
  void showDialing(common::PhoneNumber) override;
  void callAchieved(common::PhoneNumber) override;
  void showPartnerNotAvailable(common::PhoneNumber) override;

 private:
  common::PrefixedLogger logger;
  IUeGui& gui;
  common::PhoneNumber phoneNumber;
  IUserEventsHandler* handler = nullptr;
  int action = NO_ACTION;
  IUeGui::Callback callback;
  void onAcceptCallback(IUeGui::IListViewMode& menu);
};

}  // namespace ue
