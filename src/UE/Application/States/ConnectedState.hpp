#pragma once

#include "BaseState.hpp"

namespace ue {

class ConnectedState : public BaseState {
private:
  common::PhoneNumber senderPhoneNumber;

public:
  ConnectedState(Context &context);
  void handleDisconnected() final;
  void handleSms(const Sms &sms) final;
  virtual void acceptButton();
  virtual void rejectButton();
  void handleFailedSmsSend();
  void handleSendCallRequest(common::PhoneNumber) override;
  void handleSendCallDrop(common::PhoneNumber) override;
  void handleCallDrop(common::PhoneNumber) override;
  void handleCallRequest(common::PhoneNumber) override;
  void setSenderPhoneNumber(common::PhoneNumber senderPhoneNumber);
  void handleSendCallAccept(common::PhoneNumber) override;
  void
  handleUnknownRecipientCallRequest(common::PhoneNumber phoneNumber) override;
  void handleTimeout() override;
};

} // namespace ue
