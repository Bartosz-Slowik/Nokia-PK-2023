#include "UserPort.hpp"
#include "IUeGui.hpp"
#include "UeGui/ICallMode.hpp"
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
  if (smsDb.isUnreadSms()) {
    menu.addSelectionListItem("View SMS (New!)", "");
  } else {
    menu.addSelectionListItem("View SMS", "");
  }
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

void UserPort::showSms(size_t index) {
  auto sms = smsDb.retrieveSms(index);
  IUeGui::ITextMode& textMode = gui.setViewTextMode();
  if (sms) {
    textMode.setText(sms.get()->getText());
  }
}

void UserPort::showSmsList() {
  gui.showNewSms(false);
  IUeGui::IListViewMode& listMode = gui.setListViewMode();
  listMode.clearSelectionList();

  for (const auto& sms : smsDb.getSmsMessages()) {
    std::string header{""};
    if (sms.first.getFrom() == phoneNumber &&
        sms.first.getTo() == phoneNumber) {
      header = "From/To: " + common::to_string(sms.first.getTo());
    } else if (sms.first.getFrom() == phoneNumber) {
      header = " To : " + common::to_string(sms.first.getTo());
    } else if (sms.first.getTo() == phoneNumber) {
      header = "From: " + common::to_string(sms.first.getFrom());
    }

    if (!sms.first.isReceived()) {
      header = "Fail! " + header;
    }

    listMode.addSelectionListItem(header, "");
  }

  gui.setAcceptCallback([this, &listMode] { onAcceptCallback(listMode); });
}

SmsDb& UserPort::getSmsDb() {
  return smsDb;
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

void UserPort::showDialing(common::PhoneNumber phoneNumber) {
  logger.logDebug("Trying to connect with: ", phoneNumber);
  IUeGui::ITextMode& dialModeMenu = gui.setAlertMode();
  dialModeMenu.setText("Trying to\nconnect with:\n" + to_string(phoneNumber));
  gui.setAcceptCallback([&]() {});
  gui.setRejectCallback([&]() { handler->handleSendCallDrop(phoneNumber); });
}

void UserPort::showCallAchieved(common::PhoneNumber phoneNumber) {
  logger.logDebug("Talking mode with: ", phoneNumber);
  auto& callMode = gui.setAlertMode();
  callMode.setText("Call from: " + to_string(phoneNumber));
}

void UserPort::showPartnerNotAvailable(common::PhoneNumber phoneNumber) {
  gui.showPeerUserNotAvailable(phoneNumber);
  auto accept = [&]() { showConnected(); };
  auto reject = [&]() { showConnected(); };
  gui.setAcceptCallback(accept);
  gui.setRejectCallback(reject);
}

void UserPort::showCallRequest(common::PhoneNumber phoneNumber) {
  auto& alertMode = gui.setAlertMode();
  alertMode.setText("Incoming call from: " + to_string(phoneNumber));
  auto accept = [&, phoneNumber]() {
    handler->handleSendCallAccept(phoneNumber);
  };
  auto reject = [&, phoneNumber]() {
    handler->handleSendCallDrop(phoneNumber);
  };
  gui.setAcceptCallback(accept);
  gui.setRejectCallback(reject);
}

void UserPort::showNewCallTalk(common::PhoneNumber phoneNumber,
                               std::string message) {
  auto& callMode = gui.setCallMode();
  callMode.appendIncomingText(to_string(phoneNumber) + ": " + message);
}

void UserPort::showTalking(common::PhoneNumber phoneNumber) {
  auto& callMode = gui.setCallMode();
  callMode.clearIncomingText();
  auto accept = [&, phoneNumber]() {
    handler->handleSendCallTalk(phoneNumber, callMode.getOutgoingText());
    callMode.appendIncomingText("Me: " + callMode.getOutgoingText());
    callMode.clearOutgoingText();
  };
  auto reject = [&]() { handler->handleSendCallDrop({}); };
  gui.setAcceptCallback(accept);
  gui.setRejectCallback(reject);
}

}  // namespace ue
