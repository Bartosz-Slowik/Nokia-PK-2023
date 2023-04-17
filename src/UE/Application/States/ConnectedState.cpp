#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

namespace ue {

ConnectedState::ConnectedState(Context& context)
    : BaseState(context, "ConnectedState") {
  // this should show connected status
  context.user.showConnected();
}

void ConnectedState::handleDisconnected() {
  context.setState<NotConnectedState>();
}

}  // namespace ue
