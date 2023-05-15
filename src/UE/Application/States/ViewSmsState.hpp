#pragma once

#include "ConnectedState.hpp"

namespace ue {

class ViewSmsState : public ConnectedState {
 public:
  ViewSmsState(Context& context, size_t index);
  void showSmsButton() override;
  void closeSmsButton() override;
};
}  // namespace ue
