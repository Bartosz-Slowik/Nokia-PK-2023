#pragma once

#include "ConnectedState.hpp"

namespace ue {

class TalkingState : public ConnectedState {
 private:
  common::PhoneNumber caller;

 public:
  TalkingState(Context& context, common::PhoneNumber caller);
  void handleDisconnected() override;
  void handleCallRequest(common::PhoneNumber) override;
  void handleCallTalk(common::PhoneNumber phoneNumber,
                      std::string message) override;
  void handleSendCallTalk(common::PhoneNumber phoneNumber,
                          std::string message) override;
  void handleCallDrop(common::PhoneNumber) override;
  void handleSendCallDrop(common::PhoneNumber) override;
  void handleTimeout() override;
  void handleUnknownRecipientCallTalk(common::PhoneNumber) override;
};

}  // namespace ue
