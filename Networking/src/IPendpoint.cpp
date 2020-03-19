#include "IPendpoint.h"

using namespace DynabyteSoftware::Networking;
using namespace DynabyteSoftware::Networking::Internal;
using namespace std;

#ifdef USE_BOOST
#include "BoostImplementation/IPendpoint.h"

#pragma region Constructors
IPendpoint::IPendpoint(const IPaddress& address, uint16_t port, TransportProtocol protocol)
          : _implementation(make_unique<BoostImplementation::IPendpoint>(address, port, protocol))
{

}
#pragma endregion
#endif

#pragma region Constructors
IPendpoint::IPendpoint()
{
}
#pragma endregion

#pragma region IIendpoint
#pragma region Modifiers
void IPendpoint::setAddress(const IIPaddress& address)
{
  _implementation->setAddress(address);
}

void IPendpoint::setPort(uint16_t port)
{
  _implementation->setPort(port);
}

void IPendpoint::setTransportProtocol(TransportProtocol protocol)
{
  _implementation->setTransportProtocol(protocol);
}
#pragma endregion

#pragma region Observers
const IIPaddress& IPendpoint::getAddress() const
{
  return _implementation->getAddress();
}

uint16_t IPendpoint::getPort() const
{
  return _implementation->getPort();
}

TransportProtocol IPendpoint::getTransportProtocol() const
{
  return _implementation->getTransportProtocol();
}
string IPendpoint::toString() const
{
  return _implementation->toString();
}

unique_ptr<Internal::IIPendpoint> IPendpoint::clone() const
{
  auto endpoint = unique_ptr<IPendpoint>(new IPendpoint());
  endpoint->_implementation = _implementation->clone();
  return endpoint;
}
#pragma endregion
#pragma endregion