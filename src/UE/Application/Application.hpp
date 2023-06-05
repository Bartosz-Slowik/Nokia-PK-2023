#pragma once

#include "Context.hpp"
#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "SmsDb.hpp"

namespace ue {

using common::ILogger;
using common::PhoneNumber;

class Application : public IEventsHandler {
 public:
  Application(PhoneNumber phoneNumber,
              ILogger& iLogger,
              IBtsPort& bts,
              IUserPort& user,
              ITimerPort& timer,
              SmsDb& smsDB);
  ~Application();

  // ITimerEventsHandler interface
  void handleTimeout() override;

  // IBtsEventsHandler interface
  void handleDisconnected() override;
  void handleSib(common::BtsId btsId) override;
  void handleAttachAccept() override;
  void handleAttachReject() override;
  void handleSms(const Sms& sms) override;
  void handleFailedSmsSend() override;
  void handleCallRequest(common::PhoneNumber) override;
  void handleSendCallRequest(common::PhoneNumber) override;
  void handleCallAccept(common::PhoneNumber) override;
  void handleSendCallAccept(common::PhoneNumber) override;
  void handleSendCallDrop(common::PhoneNumber) override;
  void handleCallDrop(common::PhoneNumber) override;
  void handleUnknownRecipientCallRequest(common::PhoneNumber) override;
  void handleUnknownRecipientCallTalk(common::PhoneNumber) override;
  void handleCallTalk(common::PhoneNumber, std::string) override;
  void handleSendCallTalk(common::PhoneNumber, std::string) override;
  void handleStartDial() override;

 private:
  Context context;
  common::PrefixedLogger logger;
};

}  // namespace ue
