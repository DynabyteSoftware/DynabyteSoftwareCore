#include "Server.h"

using namespace DynabyteSoftware::Networking;
using namespace std;

#ifdef USE_BOOST
#include "BoostImplementation/Server.h"

#pragma region Constructors
Server::Server(uint16_t port)
      : _implementation(make_unique<BoostImplementation::Server>(port))
{
}
#pragma endregion
#endif

#pragma region IServer
future<Connection> Server::accept()
{
  return _implementation->accept();
}
#pragma endregion