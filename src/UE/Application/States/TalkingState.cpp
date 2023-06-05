#include "TalkingState.hpp"
#include "NotConnectedState.hpp"

namespace ue {

using namespace std::chrono_literals;

TalkingState::TalkingState(Context& context, common::PhoneNumber caller)
    : ConnectedState(context), caller{caller} {
  context.user.showTalking(caller);
  context.timer.startTimer(120s);
}

void TalkingState::handleDisconnected() {
  context.setState<NotConnectedState>();
}

void TalkingState::handleTimeout() {
  context.bts.sendCallDrop(caller);
  context.setState<ConnectedState>();
  context.user.showConnected();
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

void TalkingState::handleCallTalk(common::PhoneNumber phoneNumber,
                                  std::string message) {
  context.timer.stopTimer();
  context.user.showNewCallTalk(phoneNumber, message);
  context.timer.startTimer(120s);
}

void TalkingState::handleUnknownRecipientCallTalk(
    common::PhoneNumber phoneNumber) {
  context.timer.stopTimer();
  context.user.showPartnerNotAvailable(phoneNumber);
  context.setState<ConnectedState>();
}

void TalkingState::handleSendCallTalk(common::PhoneNumber phoneNumber,
                                      std::string message) {
  context.timer.stopTimer();
  context.bts.sendCallTalk(phoneNumber, message);
  context.timer.startTimer(120s);
}

void TalkingState::handleCallRequest(common::PhoneNumber phoneNumber) {
  context.bts.sendCallDrop(phoneNumber);
}

}  // namespace ue
