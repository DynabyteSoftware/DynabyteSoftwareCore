#include "BoostImplementation/Connection.h"
#include "BoostImplementation/IPendpoint.h"

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace DynabyteSoftware::Networking::BoostImplementation;
using namespace DynabyteSoftware::Networking::Internal;
using namespace std;

using DynabyteSoftware::Networking::AddressFamily;
using DynabyteSoftware::Networking::TransportProtocol;

#pragma region Constructors
Connection::Connection(const IIPendpoint& endpoint)
{
  IPendpoint boostEndpoint(endpoint.getAddress(), endpoint.getPort(), endpoint.getTransportProtocol());
  switch (endpoint.getTransportProtocol())
  {
  case TransportProtocol::TCP:
    _socket = make_unique<tcp::socket>(*_context, boostEndpoint);
    break;
  case TransportProtocol::UDP:
    _socket = make_unique<tcp::socket>(*_context, boostEndpoint);
  }
}

Connection::Connection(const shared_ptr<io_context>& context, TransportProtocol protocol, AddressFamily addressFamily)
          : _context(context)
{
  switch (protocol)
  {
  case TransportProtocol::TCP:
    _socket = make_unique<tcp::socket>(*_context);
    break;
  case TransportProtocol::UDP:
    _socket =
      make_unique<udp::socket>(*_context,
                               udp::endpoint(addressFamily == AddressFamily::IPv4 ? udp::v4() : udp::v6(), 13));
    break;
  }
}
#pragma endregion

#pragma region Modifiers
Connection::Socket& Connection::getSocket()
{
  return _socket;
}
#pragma endregion