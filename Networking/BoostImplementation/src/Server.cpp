#include "BoostImplementation/Server.h"
#include "BoostImplementation/Connection.h"
#include "Connection.h"
#include "VisitorTemplates.h"

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace DynabyteSoftware::Networking::BoostImplementation;
using namespace DynabyteSoftware::Networking::Internal;
using namespace std;

using DynabyteSoftware::Networking::TransportProtocol;
using ConnectionWrapper = DynabyteSoftware::Networking::Connection;

#pragma region Constructors
Server::Server(uint16_t port)
      : _context(make_shared<io_context>()), _acceptor(*_context, tcp::endpoint(tcp::v4(), port))
{
}
#pragma endregion

#pragma region IServer
std::future<ConnectionWrapper> Server::accept()
{
  _context->run();
  return async(launch::async,
               [this]()
               {
                 auto connection = make_shared<Connection>(_context, TransportProtocol::TCP, AddressFamily::IPv4);
                 _acceptor.accept(*get<unique_ptr<tcp::socket>>(connection->getSocket()));                 
                 return ConnectionWrapper(connection, key());
               });
}
#pragma endregion