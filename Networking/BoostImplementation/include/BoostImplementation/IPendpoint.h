#pragma once
#include "Internal/IIPendpoint.h"
#include "BoostImplementation/IPaddress.h"

#pragma warning(push)
#pragma warning(disable:26812 6385 6255 6387 6258 6001 26495 26444 26451 28251)
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/ip/udp.hpp"
#pragma warning(pop)

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
        IPendpoint(const Internal::IIPaddress& address, uint16_t port, TransportProtocol protocol);
        #pragma endregion

        #pragma region Operators
        operator boost::asio::ip::tcp::endpoint& ();
        operator boost::asio::ip::udp::endpoint& ();
        #pragma endregion

        #pragma region IIPendpoint
        #pragma region Modifiers
        virtual void setAddress(const Internal::IIPaddress& ipAddress) override;
        virtual void setPort(uint16_t port) override;
        virtual void setTransportProtocol(TransportProtocol protocol) override;
        #pragma endregion

        #pragma region Observers
        virtual const IPaddress& getAddress() const override;
        virtual uint16_t getPort() const override;
        virtual std::string toString() const override;
        virtual TransportProtocol getTransportProtocol() const override;
        virtual std::unique_ptr<Internal::IIPendpoint> clone() const override;
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