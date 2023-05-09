#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"

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

}  // namespace ue
