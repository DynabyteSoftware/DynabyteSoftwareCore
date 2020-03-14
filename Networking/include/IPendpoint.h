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
      IPendpoint(const IPaddress& address, uint32_t port);
      #pragma endregion

      #pragma region IIPendpoint
      #pragma region Modifiers
      virtual void setAddress(const Internal::IIPaddress& ipAddress) override;
      virtual void setPort(uint32_t port) override;
      #pragma endregion

      #pragma region Observers
      virtual const IPaddress& getAddress() const override;
      virtual uint32_t getPort() const override;
      virtual std::string toString() const override;
      #pragma endregion
      #pragma endregion
    private:
      #pragma region Variables
      std::unique_ptr<Internal::IIPendpoint> _implementation;
      #pragma endregion
    };
  }
}