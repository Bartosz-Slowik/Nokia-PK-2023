#include "TalkingState.hpp"

namespace ue {
using namespace std::chrono_literals;

TalkingState::TalkingState(Context& context) : ConnectedState(context) {
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
void TalkingState::handleSendCallTalk(const std::string& message) {
  context.timer.stopTimer();

  context.timer.startTimer(120s);
  context.bts.sendCallTalkMessage(message, caller);
}

void TalkingState::handleTimeout() {
  context.bts.sendCallDrop(caller);
  context.setState<ConnectedState>();
}
void TalkingState::handleReceiveCallMessage(const std::string& text) {
  context.timer.stopTimer();
  context.timer.startTimer(120s);
  context.user.showReceivedCallMessage(text);
}

}  // namespace ue
