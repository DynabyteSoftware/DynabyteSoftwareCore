#include "Server.h"

using namespace DynabyteSoftware::Networking;
using namespace std;

#pragma region IServer
future<Connection> Server::accept()
{
  return _implementation->accept();
}
#pragma endregion