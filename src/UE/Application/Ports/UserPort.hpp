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
  void showSms(size_t index) override;
  void showSmsList() override;
  SmsDb& getSmsDb() override;
  IUeGui::ISmsComposeMode& composeSms() override;
  int getAction() override;
  void acceptCallback(IUeGui::Callback acceptCallback) override;
  void rejectCallback(IUeGui::Callback rejectCallback) override;
  void showEnterPhoneNumber() override;
  void showDialing(common::PhoneNumber) override;
  void showCallAchieved(common::PhoneNumber) override;
  void showPartnerNotAvailable(common::PhoneNumber) override;
  void showCallRequest(common::PhoneNumber) override;
  void showTalking(common::PhoneNumber) override;
  void showNewCallTalk(common::PhoneNumber, std::string) override;

 private:
  common::PrefixedLogger logger;
  IUeGui& gui;
  common::PhoneNumber phoneNumber;
  IUserEventsHandler* handler = nullptr;
  int action = NO_ACTION;
  IUeGui::Callback callback;
  SmsDb smsDb;
  void onAcceptCallback(IUeGui::IListViewMode& menu);
};

}  // namespace ue
