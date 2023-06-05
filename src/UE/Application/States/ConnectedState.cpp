#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "SendingSmsState.hpp"
#include "TalkingState.hpp"
#include "ViewSmsListState.hpp"

namespace {
enum { SENDING_SMS = 0, VIEW_SMS_LIST = 1, DIAL = 2 };
}

namespace ue {

using namespace std::chrono_literals;

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
  context.user.getSmsDb().addReceivedSms(sms);
}

void ConnectedState::acceptButton() {
  switch (context.user.getAction()) {
    case VIEW_SMS_LIST:
      context.setState<ViewSmsListState>();
      break;
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
  context.user.getSmsDb().markLastSmsSentAsFailed();
}

void ConnectedState::handleSendCallRequest(
    common::PhoneNumber receiverPhoneNumber) {
  context.timer.startTimer(60s);
  context.bts.sendCallRequest(receiverPhoneNumber);
  setSenderPhoneNumber(receiverPhoneNumber);
  context.user.showDialing(receiverPhoneNumber);
}

/*void ConnectedState::handleSendCallAccept(common::PhoneNumber phoneNumber) {
  context.timer.stopTimer();
  setSenderPhoneNumber({});
  context.user.callAchieved(phoneNumber);
  context.bts.sendCallAccept(phoneNumber);
  // ToDo Implement TalkingState and set it here
}*/

void ConnectedState::setSenderPhoneNumber(common::PhoneNumber phoneNumber) {
  this->senderPhoneNumber = phoneNumber;
}

void ConnectedState::handleCallRequest(common::PhoneNumber phoneNumber) {
  using namespace std::chrono_literals;
  context.user.showCallRequest(phoneNumber);
  context.timer.startTimer(30s);
}

void ConnectedState::handleCallDrop(common::PhoneNumber phoneNumber) {
  context.user.showPartnerNotAvailable(phoneNumber);
  setSenderPhoneNumber({});
  context.user.showConnected();
  context.timer.stopTimer();
}

void ConnectedState::handleSendCallDrop(
    common::PhoneNumber receiverPhoneNumber) {
  context.timer.stopTimer();
  context.bts.sendCallDrop(senderPhoneNumber);
  setSenderPhoneNumber({});
  context.user.showConnected();
}
void ConnectedState::handleSendCallAccept(common::PhoneNumber to) {
  context.timer.stopTimer();
  setSenderPhoneNumber({});
  context.user.callAchieved(to);
  context.bts.sendCallAccept(to);
  context.setState<TalkingState>(to);
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

void ConnectedState::handleStartDial() {
  context.user.showEnterPhoneNumber();
}

void ConnectedState::handleCallAccept(common::PhoneNumber phoneNumber) {
  context.timer.stopTimer();
  setSenderPhoneNumber({});
  context.user.callAchieved(phoneNumber);
  context.setState<TalkingState>(phoneNumber);
}

}  // namespace ue
