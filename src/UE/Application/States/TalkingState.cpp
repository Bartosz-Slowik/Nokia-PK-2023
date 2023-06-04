#include "TalkingState.hpp"

namespace ue {

TalkingState::TalkingState(Context &context) : ConnectedState(context) {
  context.user.showTalking();
}

void TalkingState::handleSendCallDrop(common::PhoneNumber) {
  context.bts.sendCallDrop(caller);
  context.setState<ConnectedState>();
  context.user.showConnected();
}

void TalkingState::handleCallDrop(common::PhoneNumber phoneNumber) {
  if (phoneNumber == caller) {
    context.setState<ConnectedState>();
    context.user.showConnected();
  }
}
  
}  // namespace ue
