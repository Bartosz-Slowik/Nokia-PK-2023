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

void BaseState::handleSendCallRequest(common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleCallRequest: ", phoneNumber);
}

void BaseState::handleSendCallDrop(common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleCallDropSender: ", phoneNumber);
}

void BaseState::handleCallDrop(common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleCallDrop: ", phoneNumber);
}

void BaseState::handleCallRequest(common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleCallRequest: ", phoneNumber);
}

void BaseState::handleSendCallAccept(common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleCallAccept: ", phoneNumber);
}

void BaseState::handleUnknownRecipientCallRequest(
    common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleUnknownRecipientCallRequest: ",
                  phoneNumber);
}

void BaseState::handleCallAccept(common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleCallAccept: ", phoneNumber);
}

void BaseState::handleUnknownRecipientCallTalk(
    common::PhoneNumber phoneNumber) {
  logger.logError("Unexpected: handleUnknownRecipientCallTalk: ", phoneNumber);
}

void BaseState::handleCallTalk(common::PhoneNumber phoneNumber, std::string) {
  logger.logError("Unexpected: handleCallTalk: ", phoneNumber);
}

void BaseState::handleSendCallTalk(common::PhoneNumber phoneNumber,
                                   std::string) {
  logger.logError("Unexpected: handleSendCallTalk: ", phoneNumber);
}

void BaseState::handleStartDial() {
  logger.logError("Unexpected: handleStartDial");
}

}  // namespace ue
