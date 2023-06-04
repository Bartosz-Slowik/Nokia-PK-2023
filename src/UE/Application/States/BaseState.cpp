#include "BaseState.hpp"
#include "SmsDb.hpp"

namespace ue {

BaseState::BaseState(Context &context, const std::string &name)
    : context(context), logger(context.logger, "[" + name + "]") {
  logger.logDebug("entry");
}

BaseState::~BaseState() { logger.logDebug("exit"); }

void BaseState::handleTimeout() {
  logger.logError("Unexpected: handleTimeout");
}

void BaseState::handleSib(common::BtsId btsId) {
  logger.logError("Unexpected: handleSib: ", btsId);
}

void BaseState::handleAttachAccept() {
  logger.logError("Unexpected: handleAttachAccept");
}

void BaseState::handleAttachReject() {
  logger.logError("Unexpected: handleAttachReject");
}

void BaseState::handleDisconnected() {
  logger.logError("Uexpected: handleDisconnected");
}
void BaseState::handleSms(const Sms &) {
  logger.logError("Uexpected: handleSms");
}

void BaseState::handleFailedSmsSend() {
  logger.logError("Unexpected: handleFailedSmsSend");
}

void BaseState::handleSendCallRequest(common::PhoneNumber receiverPhoneNumber) {
  logger.logError("Uexpected: handleCallRequest: ", receiverPhoneNumber);
}

void BaseState::handleSendCallDrop(common::PhoneNumber receiverPhoneNumber) {
  logger.logError("Uexpected: handleCallDropSender: ", receiverPhoneNumber);
}

void BaseState::handleCallRequest(common::PhoneNumber phoneNumber) {
  logger.logError("Uexpected: handleCallRequest: ", phoneNumber);
}

void BaseState::handleSendCallAccept(common::PhoneNumber receiverPhoneNumber) {
  logger.logError("Uexpected: HandleSendCallAccept: ", receiverPhoneNumber);
}

void BaseState::handleUnknownRecipientCallRequest(
    common::PhoneNumber phoneNumber) {
  logger.logError("Uexpected: handleUnknownRecipientCallRequest: ",
                  phoneNumber);
}

} // namespace ue
