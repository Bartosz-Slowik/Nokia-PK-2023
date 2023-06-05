#pragma once

#include "ConnectedState.hpp"

namespace ue {

class TalkingState : public ConnectedState {
 private:
  common::PhoneNumber caller;

 public:
  TalkingState(Context& context, common::PhoneNumber caller);
  void handleTimeout() override;
  void handleCallDrop(common::PhoneNumber) override;
  void handleSendCallDrop(common::PhoneNumber) override;
  void handleCallTalk(common::PhoneNumber phoneNumber,
                      std::string message) override;
  void handleCallRequest(common::PhoneNumber) override;
  void handleUnknownRecipientCallTalk(common::PhoneNumber) override;
  void handleSendCallTalk(common::PhoneNumber phoneNumber,
                          std::string message) override;
};

}  // namespace ue
