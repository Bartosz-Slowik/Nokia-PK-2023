#include "ConnectedState.hpp"
#include "UeGui/IDialMode.hpp"

namespace ue {
class DialState : public ConnectedState {
 public:
  DialState(Context& context);

  DialState(Context& context, IUeGui::IDialMode& iDialMode);

  IUeGui::IDialMode& iDialMode;

  void acceptButton() override;
  void rejectButton() override;
};
}  // namespace ue
