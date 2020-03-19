#include "VisitorTemplates.h"
#include "BoostImplementation/Connection.h"
#include "BoostImplementation/IPendpoint.h"
#include "boost/asio/connect.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace DynabyteSoftware::Networking::BoostImplementation;
using namespace DynabyteSoftware::Networking::Internal;
using namespace std;

using DynabyteSoftware::Networking::AddressFamily;
using DynabyteSoftware::Networking::TransportProtocol;
using ErrorCode = boost::system::error_code;

#pragma region Constructors
Connection::Connection(const IIPendpoint& endpoint)
          : _context(make_shared<io_context>())
{
  IPendpoint boostEndpoint(endpoint.getAddress(), endpoint.getPort(), endpoint.getTransportProtocol());
  switch (endpoint.getTransportProtocol())
  {
  case TransportProtocol::TCP:
  {
    _socket = make_unique<tcp::socket>(*_context);
    tcp::resolver resolver(*_context);
    connect(*get< unique_ptr<tcp::socket> >(_socket), resolver.resolve(boostEndpoint));
    break;
  }
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

#pragma region IConnection
Connection& Connection::operator<<(const string& message)
{
  visit(overloaded{
        [&message](unique_ptr<tcp::socket>& socket)
        {
          for(auto bytesToSend = message.size();
              bytesToSend > 0;
              bytesToSend -= socket->write_some(buffer(message)));
        },
        [&message](unique_ptr<udp::socket>& socket)
        {
        },
    }, _socket);
  return *this;
}

Connection& Connection::operator>>(string& message)
{
  visit(overloaded{
        [&message](unique_ptr<tcp::socket>& socket)
        {
          ErrorCode error;
          array<char, 128> buf;
          auto bytesReceived = socket->read_some(buffer(buf), error);
          message.append(buf.data(), bytesReceived);
        },
        [&message](unique_ptr<udp::socket>& socket)
        {
        }
    }, _socket);
 
  return *this;
}
#pragma endregion