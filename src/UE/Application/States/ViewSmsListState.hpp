#pragma once

#include "ConnectedState.hpp"

namespace ue {

class ViewSmsListState : public ConnectedState {
 public:
  ViewSmsListState(Context& context);
  void acceptButton() override;
  void rejectButton() override;
};
}  // namespace ue
