#include "IPendpoint.h"

using namespace DynabyteSoftware::Networking;
using namespace DynabyteSoftware::Networking::Internal;
using namespace std;

#ifdef USE_BOOST
#include "BoostImplementation/IPendpoint.h"

#pragma region Constructors
IPendpoint::IPendpoint(const IPaddress& address, uint32_t port, TransportProtocol protocol)
          : _implementation(make_unique<BoostImplementation::IPendpoint>(address, port, protocol))
{

}
#pragma endregion
#endif

#pragma region IIendpoint
#pragma region Modifiers
void IPendpoint::setAddress(const IIPaddress& address)
{
  _implementation->setAddress(address);
}

void IPendpoint::setPort(uint32_t port)
{
  _implementation->setPort(port);
}
#pragma endregion

#pragma region Observers
const IIPaddress& IPendpoint::getAddress() const
{
  return _implementation->getAddress();
}

uint32_t IPendpoint::getPort() const
{
  return _implementation->getPort();
}

string IPendpoint::toString() const
{
  return _implementation->toString();
}
#pragma endregion
#pragma endregion