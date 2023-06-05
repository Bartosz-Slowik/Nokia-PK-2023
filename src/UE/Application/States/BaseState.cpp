#include "BaseState.hpp"
#include "SmsDb.hpp"

namespace ue {

BaseState::BaseState(Context& context, const std::string& name)
    : context(context), logger(context.logger, "[" + name + "]") {
  logger.logDebug("entry");
}

BaseState::~BaseState() {
  logger.logDebug("exit");
}

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
  logger.logError("Unexpected: handleDisconnected");
}

void BaseState::handleSms(const Sms&) {
  logger.logError("Unexpected: handleSms");
}

void BaseState::handleFailedSmsSend() {
  logger.logError("Unexpected: handleFailedSmsSend");
}

void BaseState::handleSendCallRequest(common::PhoneNumber receiverPhoneNumber) {
  logger.logError("Unexpected: handleCallRequest: ", receiverPhoneNumber);
}

void BaseState::handleSendCallDrop(common::PhoneNumber receiverPhoneNumber) {
  logger.logError("Unexpected: handleCallDropSender: ", receiverPhoneNumber);
}

void BaseState::handleCallDrop(common::PhoneNumber receiverPhoneNumber) {
  logger.logError("Unexpected: handleCallDrop: ", receiverPhoneNumber);
}

void BaseState::handleCallRequest(common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleCallRequest: ", phoneNumber);
}

void BaseState::handleSendCallAccept(common::PhoneNumber receiverPhoneNumber) {
  logger.logError("Unexpected: handleCallAccept: ", receiverPhoneNumber);
}

void BaseState::handleUnknownRecipientCallRequest(
    common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleUnknownRecipientCallRequest: ",
                  phoneNumber);
}
void BaseState::handleSendCallTalk(const std::string& message) {
  logger.logError("Unexpected: handleSendCallTalk", message);
}
void BaseState::handleReceiveCallMessage(const std::string& text) {
  logger.logError("Unexpected: handleReceiveCallMessage", text);
}

}  // namespace ue
