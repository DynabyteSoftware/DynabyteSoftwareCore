#include "BoostImplementation/Server.h"

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace DynabyteSoftware::Networking;
using namespace DynabyteSoftware::Networking::BoostImplementation;
using namespace DynabyteSoftware::Networking::Internal;
using namespace std;

#pragma region Constructors
Server::Server(uint16_t port, TransportProtocol protocol)
      : _context(make_shared<io_context>())
{
  switch (protocol)
  {
  case TransportProtocol::TCP:
    _acceptor = make_unique<tcp::acceptor>(*_context, tcp::endpoint(tcp::v4(), port));
    break;
  case TransportProtocol::UDP:
    _acceptor = make_unique<udp::socket>(*_context, udp::endpoint(udp::v4(), port));
    break;
  }
}
#pragma endregion