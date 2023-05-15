#include "Sms.hpp"
#include <chrono>

namespace ue {

Sms::Sms(const std::string& text,
         const common::PhoneNumber& from,
         const common::PhoneNumber& to,
         bool received,
         const std::chrono::time_point<std::chrono::system_clock>& receiveTime)
    : text(text),
      from(from),
      to(to),
      received(received),
      receiveTime(receiveTime) {}

Sms::Sms(const std::string& text,
         const common::PhoneNumber& from,
         const common::PhoneNumber& to)
    : text(text), from(from), to(to) {}

void Sms::markAsNotReceived() {
  received = false;
}

bool Sms::isReceived() const {
  return received;
}

std::string Sms::getText() const {
  return text;
}

const common::PhoneNumber& Sms::getFrom() const {
  return from;
};

const common::PhoneNumber& Sms::getTo() const {
  return to;
}

const std::chrono::time_point<std::chrono::system_clock>& Sms::getReceiveTime()
    const {
  return receiveTime;
}

}  // namespace ue
