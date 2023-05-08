#pragma once
#include <Messages/PhoneNumber.hpp>
#include <chrono>

namespace ue {

class Sms {
 private:
  std::string text;
  common::PhoneNumber from;
  common::PhoneNumber to;
  bool read = false;
  bool received = true;
  std::chrono::time_point<std::chrono::system_clock> receiveTime;

 public:
  Sms();

  Sms(const std::string& text,
      const common::PhoneNumber& from,
      const common::PhoneNumber& to);

  Sms(const std::string& text,
      const common::PhoneNumber& from,
      const common::PhoneNumber& to,
      bool read,
      bool received,
      const std::chrono::time_point<std::chrono::system_clock>& receiveTime);

  void markAsRead();
  void markAsNotReceived();
  bool isRead() const;
  bool isReceived() const;
  std::string getText() const;

  const common::PhoneNumber& getFrom() const;

  const common::PhoneNumber& getTo() const;

  const std::chrono::time_point<std::chrono::system_clock>& getReceiveTime()
      const;

  bool operator==(const Sms& other) const {
    return (this->text == other.text && this->from == other.from &&
            this->to == other.to);
  }
};

}  // namespace ue
