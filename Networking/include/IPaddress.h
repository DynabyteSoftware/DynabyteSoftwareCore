#pragma once
#include "IAssignable.h"
#include "Internal/IIPaddress.h"

namespace DynabyteSoftware
{
  namespace Networking
  {
    class IPaddress
      : public Internal::IIPaddress, public virtual IAssignable<IPaddress>
    {
    public:
      #pragma region Constructors
      IPaddress(const std::array<std::byte, 4>& bytesIPv4);
      IPaddress(const std::array<std::byte, 8>& bytesIPv6);
      IPaddress(const std::string& address);

      IPaddress(const IPaddress& original);
      IPaddress(IPaddress&& old);
      #pragma endregion

      #pragma region IIPaddress
      virtual AddressFamily getAddressFamily() const override;
      virtual std::vector<std::byte> getAddressBytes() const override;
      virtual std::string toString() const override;
      #pragma endregion

      #pragma region IAssignable
      virtual IPaddress& operator=(const IPaddress& rhs) override;
      virtual IPaddress& operator=(IPaddress&& rhs) override;
      #pragma endregion
    private:
      #pragma region Variables
      std::unique_ptr<Internal::IIPaddress> _implementation;
      #pragma endregion
    };
  }
}