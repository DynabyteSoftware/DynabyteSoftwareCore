#include "EnumFlagUtilities.h"
#include "Server.h"

enum struct ErrorCodes
{
  OK = 0,
  ExceptionNotThrown = -0x1
};

FLAGS(ErrorCodes)

using namespace DynabyteSoftware::Networking;

int main()
{
  ErrorCodes errorCode = ErrorCodes::OK;
  Server server(12000);
  auto serverConnection = server.accept();
  Connection connection(IPendpoint(IPaddress("127.0.0.1"), 12000, TransportProtocol::TCP));

  return static_cast<int>(errorCode);
}