#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue {

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger& iLogger,
                         IBtsPort& bts,
                         IUserPort& user,
                         ITimerPort& timer,
                         SmsDb& smsDb)
    : context{iLogger, bts, user, timer, smsDb}, logger(iLogger, "[APP] ") {
  logger.logInfo("Started");
  context.setState<NotConnectedState>();
}

Application::~Application() {
  logger.logInfo("Stopped");
}

void Application::handleTimeout() {
  context.state->handleTimeout();
}

void Application::handleDisconnected() {
  context.state->handleDisconnected();
}

void Application::handleSib(common::BtsId btsId) {
  context.state->handleSib(btsId);
}

void Application::handleAttachAccept() {
  context.state->handleAttachAccept();
}

void Application::handleAttachReject() {
  context.state->handleAttachReject();
}
void Application::handleSms(const Sms& sms) {
  context.state->handleSms(sms);
}

void Application::handleFailedSmsSend() {
  context.state->handleFailedSmsSend();
}

void Application::handleSendCallRequest(
    common::PhoneNumber receiverPhoneNumber) {
  context.state->handleSendCallRequest(receiverPhoneNumber);
}

void Application::handleSendCallDrop(common::PhoneNumber receiverPhoneNumber) {
  context.state->handleSendCallDrop(receiverPhoneNumber);
}

void Application::handleCallRequest(common::PhoneNumber phoneNumber) {
  context.state->handleCallRequest(phoneNumber);
}

void Application::handleSendCallAccept(common::PhoneNumber phoneNumber) {
  context.state->handleSendCallAccept(phoneNumber);
}

void Application::handleUnknownRecipientCallRequest(
    common::PhoneNumber phoneNumber) {
  context.state->handleUnknownRecipientCallRequest(phoneNumber);
}
}  // namespace ue
