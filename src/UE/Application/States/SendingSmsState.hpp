#pragma once

#include "ConnectedState.hpp"
#include "UeGui/ISmsComposeMode.hpp"

namespace ue {
class SendingSmsState : public ConnectedState {
 private:
  IUeGui::ISmsComposeMode& iSmsComposeMode;

 public:
  SendingSmsState(Context& context);

  void acceptButton() override;
  void rejectButton() override;
};
}  // namespace ue
