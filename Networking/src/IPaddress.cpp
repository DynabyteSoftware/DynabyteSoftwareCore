#include "IPaddress.h"

using namespace DynabyteSoftware::Networking;
using namespace DynabyteSoftware::Networking::Internal;
using namespace std;

#ifdef USE_BOOST
#include "BoostImplementation/IPaddress.h"

#pragma region Constructors
IPaddress::IPaddress(const array<byte, 4>& bytesIPv4)
  : _implementation(make_unique<BoostImplementation::IPaddress>(bytesIPv4))
{
}

IPaddress::IPaddress(const array<byte, 8>& bytesIPv6)
         : _implementation(make_unique<BoostImplementation::IPaddress>(bytesIPv6))
{
}

IPaddress::IPaddress(const string& address)
         : _implementation(make_unique<BoostImplementation::IPaddress>(address))
{
}
#pragma endregion
#endif

#pragma region Constructors
IPaddress::IPaddress(const IPaddress& original)
         : _implementation(original._implementation->clone())
{
}

IPaddress::IPaddress(IPaddress&& old) noexcept
         : _implementation(move(old._implementation))
{
}
#pragma endregion

#pragma region IPaddress
AddressFamily IPaddress::getAddressFamily() const
{
  return _implementation->getAddressFamily();
}

vector<byte> IPaddress::getAddressBytes() const
{
  return _implementation->getAddressBytes();
}

string IPaddress::toString() const
{
  return _implementation->toString();
}

unique_ptr<IIPaddress> IPaddress::clone() const
{
  return make_unique<IPaddress>(*this);
}
#pragma endregion

#pragma region IAssignable
IPaddress& IPaddress::operator=(const IPaddress& rhs)
{
  _implementation = rhs._implementation->clone();
  return *this;
}

IPaddress& IPaddress::operator=(IPaddress&& rhs) noexcept
{
  _implementation = move(rhs._implementation);
  return *this;
}
#pragma region

