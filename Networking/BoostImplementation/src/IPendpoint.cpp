#include "BoostImplementation/IPendpoint.h"
#include "Internal/IIPaddress.h"
#include "Exception.h"

using namespace DynabyteSoftware::Networking;
using namespace DynabyteSoftware::Networking::BoostImplementation;
using namespace DynabyteSoftware::Networking::Internal;
using namespace boost::asio::ip;
using namespace std;

#pragma region Variant Visitor
template<typename... Ts> struct overloaded : Ts... {using Ts::operator()...; };
template<typename... Ts> overloaded(Ts...)->overloaded<Ts...>;
#pragma endregion

#pragma region Constructors
IPendpoint::IPendpoint(const IIPaddress& address, uint32_t port, TransportProtocol protocol)
          : _address(address.toString())
{
  if(port > MaxPort)
    THROW(Exception, "Port number exceeds max port number value")

  switch (protocol)
  {
  case TransportProtocol::TCP:
    _endpoint = tcp::endpoint(_address, port);
    break;
  case TransportProtocol::UDP:
    _endpoint = udp::endpoint(_address, port);
    break;
  }
}
#pragma endregion

#pragma region IIPendpoint
#pragma region Modifiers
void IPendpoint::setAddress(const IIPaddress& ipAddress)
{
  visit([&ipAddress](auto&& arg) {arg.address(make_address(ipAddress.toString())); }, _endpoint);
}

void IPendpoint::setPort(uint32_t port)
{
  visit([&port](auto&& arg) {arg.port(port); }, _endpoint);
}

void IPendpoint::setTransportProtocol(TransportProtocol protocol)
{
  if (getTransportProtocol() != protocol)
  {
    switch (protocol)
    {
    case TransportProtocol::TCP:
    {
      const auto& endpoint = get<udp::endpoint>(_endpoint);
      _endpoint = tcp::endpoint(_address, endpoint.port());
      break;
    }
    case TransportProtocol::UDP:
    {
      const auto& endpoint = get<tcp::endpoint>(_endpoint);
      _endpoint = udp::endpoint(_address, endpoint.port());
      break;
    }
    }
  }
}
#pragma endregion

#pragma region Observers
const IPaddress& IPendpoint::getAddress() const
{
  return _address;
}

uint32_t IPendpoint::getPort() const
{
  return visit([](auto&& arg)->uint32_t {return arg.port();}, _endpoint);
}

string IPendpoint::toString() const
{
  return _address.toString() + ':' + to_string(getPort());
}

TransportProtocol IPendpoint::getTransportProtocol() const
{
  return visit(overloaded{
                [](const tcp::endpoint&)->TransportProtocol {return TransportProtocol::TCP; },
                [](const udp::endpoint&)->TransportProtocol {return TransportProtocol::UDP; },
    }, _endpoint);
}
#pragma endregion
#pragma endregion