#pragma once
#include "IAssignable.h"
#include "Internal/IIPaddress.h"
#include "NetworkingExports.h"

namespace DynabyteSoftware
{
  namespace Networking
  {
    class IPaddress final
      : public Internal::IIPaddress, public virtual IAssignable<IPaddress>
    {
    public:
      #pragma region Constructors
      NETWORKING_EXPORT IPaddress(const std::array<std::byte, 4>& bytesIPv4);
      NETWORKING_EXPORT IPaddress(const std::array<std::byte, 8>& bytesIPv6);
      NETWORKING_EXPORT IPaddress(const std::string& address);

      NETWORKING_EXPORT IPaddress(const IPaddress& original);
      NETWORKING_EXPORT IPaddress(IPaddress&& old) noexcept;
      #pragma endregion

      #pragma region IIPaddress
      NETWORKING_EXPORT inline virtual AddressFamily getAddressFamily() const override;
      NETWORKING_EXPORT inline virtual std::vector<std::byte> getAddressBytes() const override;
      NETWORKING_EXPORT inline virtual std::string toString() const override;
      NETWORKING_EXPORT inline virtual std::unique_ptr<IIPaddress> clone() const override;
      #pragma endregion

      #pragma region IAssignable
      NETWORKING_EXPORT inline virtual IPaddress& operator=(const IPaddress& rhs) override;
      NETWORKING_EXPORT inline virtual IPaddress& operator=(IPaddress&& rhs) noexcept override;
      #pragma endregion
    private:
      #pragma region Variables
      std::unique_ptr<Internal::IIPaddress> _implementation;
      #pragma endregion
    };
  }
}