#pragma once
#include "Internal/IIPaddress.h"

#pragma warning(push)
#pragma warning(disable:26812 6385 6255 6387 6258 6001 26495 26444 26451 28251)
#include "boost/asio/ip/address.hpp"
#pragma warning(pop)

namespace DynabyteSoftware
{
  namespace Networking
  {
    namespace BoostImplementation
    {
      class IPaddress
        : public virtual Internal::IIPaddress
      {
      public:
        #pragma region Constructors
        IPaddress(const std::array<std::byte, 4>& bytesIPv4);
        IPaddress(const std::array<std::byte, 8>& bytesIPv6);
        IPaddress(const std::string& address);
        #pragma endregion

        #pragma region IIPaddress
        virtual AddressFamily getAddressFamily() const override;
        virtual std::vector<std::byte> getAddressBytes() const override;
        virtual std::string toString() const override;
        virtual std::unique_ptr<Internal::IIPaddress> clone() const override;
        #pragma endregion

        #pragma region Operators
        operator boost::asio::ip::address&();
        operator const boost::asio::ip::address&() const;
        #pragma endregion
      private:
        boost::asio::ip::address _address;
      };
    }
  }
}