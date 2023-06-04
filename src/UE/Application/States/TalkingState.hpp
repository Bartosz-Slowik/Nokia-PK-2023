#pragma once

#include "ConnectedState.hpp"

namespace ue {
  
class TalkingState : public ConnectedState {
 private:
  common::PhoneNumber caller;

 public:
  TalkingState(Context &context);
  void handleCallDrop(common::PhoneNumber) override;
  void handleSendCallDrop(common::PhoneNumber) override;
};

}  // namespace ue
