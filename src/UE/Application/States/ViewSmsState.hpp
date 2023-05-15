#pragma once

#include "ConnectedState.hpp"

namespace ue {

class ViewSmsState : public ConnectedState {
 public:
  ViewSmsState(Context& context, size_t index);
  void acceptButton() override;
  void rejectButton() override;
};
}  // namespace ue
