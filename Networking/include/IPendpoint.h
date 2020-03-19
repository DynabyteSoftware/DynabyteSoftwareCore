#pragma once
#include "Internal/IIPendpoint.h"
#include "IPaddress.h"
#include <memory>

namespace DynabyteSoftware
{
  namespace Networking
  {
    class IPendpoint final
      : public Internal::IIPendpoint
    {
    public:
      #pragma region Constructors
      NETWORKING_EXPORT IPendpoint(const IPaddress& address, uint32_t port,
                                   TransportProtocol protocol = TransportProtocol::TCP);
      #pragma endregion

      #pragma region IIPendpoint
      #pragma region Modifiers
      NETWORKING_EXPORT inline virtual void setAddress(const Internal::IIPaddress& ipAddress) override;
      NETWORKING_EXPORT inline virtual void setPort(uint32_t port) override;
      #pragma endregion

      #pragma region Observers
      NETWORKING_EXPORT inline virtual const Internal::IIPaddress& getAddress() const override;
      NETWORKING_EXPORT inline virtual uint32_t getPort() const override;
      NETWORKING_EXPORT inline virtual std::string toString() const override;
      #pragma endregion
      #pragma endregion
    private:
      #pragma region Variables
      std::unique_ptr<Internal::IIPendpoint> _implementation;
      #pragma endregion
    };
  }
}