#include "TalkingState.hpp"

namespace ue {
TalkingState::TalkingState(Context &context) : ConnectedState(context) {
  context.user.showTalking();
}
} // namespace ue
