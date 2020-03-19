#pragma once
#include <cstdint>
#include <string>
#include "ICloneable.h"
#include "TransportProtocol.h"

namespace DynabyteSoftware
{
  namespace Networking
  {
    namespace Internal
    {
      class IIPaddress;

      class IIPendpoint
        : public ICloneable<IIPendpoint>
      {
      public:
        #pragma region Constants
        static constexpr uint16_t MaxPort = 0x0000FFFF;
        #pragma endregion

        #pragma region Modifiers
        virtual void setAddress(const IIPaddress& ipAddress) = 0;
        virtual void setPort(uint16_t port) = 0;
        virtual void setTransportProtocol(TransportProtocol protocol) = 0;
        #pragma endregion

        #pragma region Observers
        virtual const IIPaddress& getAddress() const = 0;
        virtual uint16_t getPort() const = 0;
        virtual TransportProtocol getTransportProtocol() const = 0;
        virtual std::string toString() const = 0;
        #pragma endregion
      };
    }
  }
}