#include "SendingSmsState.hpp"
#include "../Sms.hpp"

namespace ue {
SendingSmsState::SendingSmsState(Context& context)
    : ConnectedState(context), iSmsComposeMode(context.user.composeSms()) {
  iSmsComposeMode.clearSmsText();
}

void SendingSmsState::acceptButton() {
  std::string text = iSmsComposeMode.getSmsText();
  common::PhoneNumber toPhoneNumber = iSmsComposeMode.getPhoneNumber();
  Sms sms = Sms{text, context.bts.getOwnPhoneNumber(), toPhoneNumber, false,
                true, std::chrono::system_clock::now()};
  context.smsDb.addSms(sms);
  context.bts.sendSms(sms);
  context.setState<ConnectedState>();
}

void SendingSmsState::rejectButton() {
  context.setState<ConnectedState>();
}

}  // namespace ue
