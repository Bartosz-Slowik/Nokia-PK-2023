#include "BtsPort.hpp"
#include <chrono>
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"

namespace ue {

BtsPort::BtsPort(common::ILogger& logger,
                 common::ITransport& transport,
                 common::PhoneNumber phoneNumber)
    : logger(logger, "[BTS-PORT]"),
      transport(transport),
      phoneNumber(phoneNumber) {}

void BtsPort::start(IBtsEventsHandler& handler) {
  transport.registerMessageCallback(
      [this](BinaryMessage msg) { handleMessage(msg); });
  transport.registerDisconnectedCallback([this]() { handleDisconnected(); });
  this->handler = &handler;
}

void BtsPort::stop() {
  transport.registerMessageCallback(nullptr);
  transport.registerDisconnectedCallback(nullptr);
  handler = nullptr;
}

void BtsPort::handleDisconnected() {
  handler->handleDisconnected();
}

void BtsPort::handleMessage(BinaryMessage msg) {
  try {
    common::IncomingMessage reader{msg};
    auto msgId = reader.readMessageId();
    auto from = reader.readPhoneNumber();
    auto to = reader.readPhoneNumber();

    switch (msgId) {
      case common::MessageId::Sib: {
        auto btsId = reader.readBtsId();
        handler->handleSib(btsId);
        break;
      }
      case common::MessageId::AttachResponse: {
        bool accept = reader.readNumber<std::uint8_t>() != 0u;
        if (accept)
          handler->handleAttachAccept();
        else
          handler->handleAttachReject();
        break;
      }
      case common::MessageId::Sms: {
        auto action = reader.readNumber<std::uint8_t>();
        if (action == 0) {
          const auto sms = Sms{reader.readRemainingText(), from, to, true,
                               std::chrono::system_clock::now()};
          handler->handleSms(sms);
        }
        break;
      }
      case common::MessageId::CallRequest: {
        handler->handleCallRequest(from);
        break;
      }
      case common::MessageId::CallAccepted: {
        break;
      }
      case common::MessageId::CallDropped: {
        break;
      }
      case common::MessageId::UnknownRecipient: {
        auto failHeader = reader.readMessageHeader();
        if (failHeader.messageId == common::MessageId::Sms)
          handler->handleFailedSmsSend();
        else
          handler->handleUnknownRecipientCallRequest(from);
        logger.logInfo("Handle for unknown recipient");
      }
      default:
        logger.logError("unknow message: ", msgId, ", from: ", from);
    }
  } catch (std::exception const& ex) {
    logger.logError("handleMessage error: ", ex.what());
  }
}

void BtsPort::sendAttachRequest(common::BtsId btsId) {
  logger.logDebug("sendAttachRequest: ", btsId);
  common::OutgoingMessage msg{common::MessageId::AttachRequest, phoneNumber,
                              common::PhoneNumber{}};
  msg.writeBtsId(btsId);
  transport.sendMessage(msg.getMessage());
}

common::PhoneNumber BtsPort::getOwnPhoneNumber() {
  return phoneNumber;
}

void BtsPort::sendSms(const Sms& sms) {
  common::OutgoingMessage outgoingMessage = common::OutgoingMessage(
      common::MessageId::Sms, sms.getFrom(), sms.getTo());
  outgoingMessage.writeNumber(static_cast<uint8_t>(0));

  outgoingMessage.writeText(sms.getText());

  transport.sendMessage(outgoingMessage.getMessage());
}

void BtsPort::sendCallRequest(common::PhoneNumber receiverPhoneNumber) {
  common::OutgoingMessage msg{common::MessageId::CallRequest, phoneNumber,
                              receiverPhoneNumber};
  transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallAccept(common::PhoneNumber receiverPhoneNumber) {
  logger.logDebug("sendCallAccept: ", receiverPhoneNumber);
  common::OutgoingMessage msg{common::MessageId::CallAccepted, phoneNumber,
                              receiverPhoneNumber};
  transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallDrop(common::PhoneNumber receiverPhoneNumber) {
  logger.logDebug("sendCallDrop: ", receiverPhoneNumber);
  common::OutgoingMessage msg{common::MessageId::CallDropped, phoneNumber,
                              receiverPhoneNumber};
  transport.sendMessage(msg.getMessage());
}

}  // namespace ue
