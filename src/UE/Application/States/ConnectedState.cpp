#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "SendingSmsState.hpp"

namespace {
enum { SENDING_SMS = 0, VIEW_SMS_LIST = 1, DIAL = 2 };
}

namespace ue {

ConnectedState::ConnectedState(Context& context)
    : BaseState(context, "ConnectedState") {
  context.user.acceptCallback([this] { acceptButton(); });
  context.user.rejectCallback([this] { rejectButton(); });
  // this should show connected status
  context.user.showConnected();
}

void ConnectedState::handleDisconnected() {
  context.setState<NotConnectedState>();
}
void ConnectedState::handleSms(const Sms& sms) {
  logger.logInfo("sms: from ", sms.getFrom(), " message: ", sms.getText(),
                 " is being handled");
  context.user.showNewSmsNotification();
  context.smsDb.addReceivedSms(sms);
}

void ConnectedState::acceptButton() {
  switch (context.user.getAction()) {
    case SENDING_SMS:
      context.setState<SendingSmsState>();
      break;
    case DIAL:
      context.user.showEnterPhoneNumber();
      break;
  }
}

void ConnectedState::rejectButton() {}

void ConnectedState::handleFailedSmsSend() {
  context.smsDb.markLastSmsSentAsFailed();
}

void ConnectedState::handleSendCallRequest(
    common::PhoneNumber receiverPhoneNumber) {
  using namespace std::chrono_literals;
  context.timer.startTimer(60000ms);
  context.bts.sendCallRequest(receiverPhoneNumber);
  setSenderPhoneNumber(receiverPhoneNumber);
  context.user.showDialing(receiverPhoneNumber);
}

void ConnectedState::handleSendCallAccept(common::PhoneNumber phoneNumber) {
  context.timer.stopTimer();
  setSenderPhoneNumber({});
  context.user.callAchieved(phoneNumber);
  context.bts.sendCallAccept(phoneNumber);
  // context.setState<TalkingState>(phoneNumber);
}

void ConnectedState::setSenderPhoneNumber(common::PhoneNumber phoneNumber) {
  this->senderPhoneNumber = phoneNumber;
}

void ConnectedState::handleCallRequest(common::PhoneNumber phoneNumber) {}

void ConnectedState::handleSendCallDrop(
    common::PhoneNumber receiverPhoneNumber) {
  context.timer.stopTimer();
  context.bts.sendCallDrop(senderPhoneNumber);
  setSenderPhoneNumber({});
  context.user.showConnected();
}

void ConnectedState::handleUnknownRecipientCallRequest(
    common::PhoneNumber phoneNumber) {
  context.timer.stopTimer();
  context.user.showPartnerNotAvailable(senderPhoneNumber);
  setSenderPhoneNumber({});
}

void ConnectedState::handleTimeout() {
  context.user.showConnected();
  handleSendCallDrop({});
}

}  // namespace ue
