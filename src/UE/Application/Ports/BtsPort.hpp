#pragma once

#include "IBtsPort.hpp"
#include "ITransport.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue {

class BtsPort : public IBtsPort {
 public:
  BtsPort(common::ILogger& logger,
          common::ITransport& transport,
          common::PhoneNumber phoneNumber);
  void start(IBtsEventsHandler& handler);
  void stop();

  void sendAttachRequest(common::BtsId) override;
  common::PhoneNumber getOwnPhoneNumber() override;
  void sendSms(const Sms& sms) override;
  void sendCallRequest(common::PhoneNumber) override;
  void sendCallAccept(common::PhoneNumber) override;
  void sendCallDrop(common::PhoneNumber) override;

 private:
  void handleDisconnected();
  void handleMessage(BinaryMessage msg);

  common::PrefixedLogger logger;
  common::ITransport& transport;
  common::PhoneNumber phoneNumber;

  IBtsEventsHandler* handler = nullptr;
};

}  // namespace ue
