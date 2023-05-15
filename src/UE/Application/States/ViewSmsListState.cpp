#include "ViewSmsListState.hpp"
#include "ConnectedState.hpp"
#include "ViewSmsState.hpp"

namespace ue {

ViewSmsListState::ViewSmsListState(Context& context) : ConnectedState(context) {
  context.user.showSmsList();
}

void ViewSmsListState::acceptButton() {
  int action = context.user.getAction();
  context.setState<ViewSmsState>(action);
}

void ViewSmsListState::rejectButton() {
  context.setState<ConnectedState>();
}
}  // namespace ue
