#pragma once
#include "Internal/IIPendpoint.h"
#include "BoostImplementation/IPaddress.h"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/ip/udp.hpp"
#include <variant>

namespace DynabyteSoftware
{
  namespace Networking
  {
    namespace BoostImplementation
    {
      class IPendpoint final
        : public Internal::IIPendpoint
      {
      public:
        #pragma region Constructors
        IPendpoint(const Internal::IIPaddress& address, uint32_t port, TransportProtocol protocol);
        #pragma endregion

        #pragma region IIPendpoint
        #pragma region Modifiers
        virtual void setAddress(const Internal::IIPaddress& ipAddress) override;
        virtual void setPort(uint32_t port) override;
        virtual void setTransportProtocol(TransportProtocol protocol) override;
        #pragma endregion

        #pragma region Observers
        virtual const IPaddress& getAddress() const override;
        virtual uint32_t getPort() const override;
        virtual std::string toString() const override;
        virtual TransportProtocol getTransportProtocol() const override;
        #pragma endregion
        #pragma endregion
      private:
        #pragma region Variables
        IPaddress _address;
        std::variant<boost::asio::ip::tcp::endpoint, boost::asio::ip::udp::endpoint> _endpoint;
        #pragma endregion
      };
    }
  }
}