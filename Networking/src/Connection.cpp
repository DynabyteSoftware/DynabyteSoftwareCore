#include "Connection.h"

using namespace DynabyteSoftware;
using namespace DynabyteSoftware::Networking;
using namespace std;

#ifdef USE_BOOST
#include "BoostImplementation/Connection.h"

#pragma region Constructors
Connection::Connection()
{
}

Connection::Connection(const IPendpoint& endpoint)
          : _implementation(make_shared<BoostImplementation::Connection>(endpoint))
{
}

Connection::Connection(const shared_ptr<Internal::IConnection>& implementation, const Key<Internal::IServer>&)
          : _implementation(implementation)
{
}
#pragma endregion
#endif

#pragma region Constructors


Connection::Connection(Connection&& old)
  : _implementation(move(old._implementation))
{

}
#pragma endregion

#pragma region Operator
Connection& Connection::operator=(Connection&& old)
{
  _implementation = move(old._implementation);
  return *this;
}
#pragma endregion