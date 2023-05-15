#include "ViewSmsState.hpp"
#include "ConnectedState.hpp"
#include "ViewSmsListState.hpp"

namespace ue {

ViewSmsState::ViewSmsState(Context& context, size_t index)
    : ConnectedState(context) {
  context.user.showSms(index);
}

void ViewSmsState::acceptButton() {}

void ViewSmsState::rejectButton() {
  context.setState<ViewSmsListState>();
}
}  // namespace ue
