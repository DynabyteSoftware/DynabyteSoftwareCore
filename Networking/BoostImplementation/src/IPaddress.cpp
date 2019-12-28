#include "BoostImplementation/IPaddress.h"

using namespace DynabyteSoftware::Networking;
using namespace DynabyteSoftware::Networking::BoostImplementation;
using namespace DynabyteSoftware::Networking::Internal;
using namespace boost::asio::ip;
using namespace std;

#pragma region Constructors
IPaddress::IPaddress(const array<byte, 4>& bytesIPv4)
         : _address(make_address_v4(reinterpret_cast<const address_v4::bytes_type&>(bytesIPv4)))
{
}

IPaddress::IPaddress(const array<byte, 8>& bytesIPv6)
         : _address(make_address_v6(reinterpret_cast<const address_v6::bytes_type&>(bytesIPv6)))
{
}

IPaddress::IPaddress(const string& address)
         : _address(make_address(address))
{
}
#pragma endregion

#pragma region IPaddress
AddressFamily IPaddress::getAddressFamily() const
{
  return _address.is_v4() ? AddressFamily::IPv4 : AddressFamily::IPv6;
}

vector<byte> IPaddress::getAddressBytes() const
{
  if (_address.is_v4())
  {
    const auto bytes = reinterpret_cast<const array<byte, 4>&>(_address.to_v4().to_bytes());
    return vector<byte>(bytes.cbegin(), bytes.cend());
  }

  const auto bytes = reinterpret_cast<const array<byte, 8>&>(_address.to_v6().to_bytes());
  return vector<byte>(bytes.cbegin(), bytes.cend());
}

string IPaddress::toString() const
{
  return _address.to_string();
}

unique_ptr<IIPaddress> IPaddress::clone() const
{
  return make_unique<IPaddress>(*this);
}
#pragma endregion