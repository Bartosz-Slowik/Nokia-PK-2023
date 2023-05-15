#include "UserPort.hpp"
#include "UeGui/IDialMode.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "UeGui/ITextMode.hpp"

namespace ue {

UserPort::UserPort(common::ILogger& logger,
                   IUeGui& gui,
                   common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"), gui(gui), phoneNumber(phoneNumber) {}

void UserPort::start(IUserEventsHandler& handler) {
  this->handler = &handler;
  gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop() {
  handler = nullptr;
}

void UserPort::showNotConnected() {
  gui.showNotConnected();
}

void UserPort::showConnecting() {
  gui.showConnecting();
}

void UserPort::showConnected() {
  IUeGui::IListViewMode& menu = gui.setListViewMode();
  menu.clearSelectionList();
  menu.addSelectionListItem("Compose SMS", "");
  menu.addSelectionListItem("View SMS", "");
  menu.addSelectionListItem("Dial", "");

  gui.setAcceptCallback([this, &menu] { onAcceptCallback(menu); });
}
void UserPort::showNewSmsNotification() {
  gui.showNewSms(true);
}

IUeGui::ISmsComposeMode& UserPort::composeSms() {
  IUeGui::ISmsComposeMode& smsComposer = gui.setSmsComposeMode();
  smsComposer.clearSmsText();
  smsComposer.getPhoneNumber();
  smsComposer.getSmsText();

  return smsComposer;
}

int UserPort::getAction() {
  return action;
}

void UserPort::acceptCallback(IUeGui::Callback acceptCallback) {
  this->callback = acceptCallback;
  gui.setAcceptCallback(acceptCallback);
}

void UserPort::onAcceptCallback(IUeGui::IListViewMode& menu) {
  IUeGui::IListViewMode::OptionalSelection pair = menu.getCurrentItemIndex();
  if (!pair.first) {
    action = -1;
  } else {
    action = pair.second;
  }
  callback();
}

void UserPort::rejectCallback(IUeGui::Callback rejectCallback) {
  gui.setRejectCallback(rejectCallback);
}

void UserPort::showEnterPhoneNumber() {
  auto& dialModeMenu = gui.setDialMode();
  gui.setAcceptCallback(
      [&]() { handler->handleSendCallRequest(dialModeMenu.getPhoneNumber()); });
  gui.setRejectCallback(
      [&]() { handler->handleSendCallDrop(dialModeMenu.getPhoneNumber()); });
}

void UserPort::showDialing(common::PhoneNumber senderPhoneNumber) {
  logger.logDebug("Trying to connect with: ", senderPhoneNumber);
  IUeGui::ITextMode& dialModeMenu = gui.setAlertMode();
  dialModeMenu.setText("Trying to\nconnect with:\n" +
                       to_string(senderPhoneNumber));
  gui.setAcceptCallback([&]() {});
  gui.setRejectCallback(
      [&]() { handler->handleSendCallDrop(senderPhoneNumber); });
}

void UserPort::callAchieved(common::PhoneNumber senderPhoneNumber) {
  logger.logDebug("Talking mode with: ", senderPhoneNumber);
  auto& callMode = gui.setAlertMode();
  callMode.setText("Call from: " + to_string(senderPhoneNumber));
}

void UserPort::showPartnerNotAvailable(common::PhoneNumber phoneNumber) {
  gui.showPeerUserNotAvailable(phoneNumber);
  auto accept = [&]() { showConnected(); };
  auto reject = [&]() { showConnected(); };
  gui.setAcceptCallback(accept);
  gui.setRejectCallback(reject);
}

}  // namespace ue
