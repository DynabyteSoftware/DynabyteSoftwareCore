#include "EnumFlagUtilities.h"
#include "Server.h"
#include <iostream>

enum struct ErrorCodes
{
  OK = 0,
  ExceptionNotThrown = -0x1
};

FLAGS(ErrorCodes)

using namespace DynabyteSoftware::Networking;
using namespace std;

void handleConnection(Connection server)
{
  string message;
  server >> message;
  cout << "Server received: " << message << endl;
  if (message == "You got a dead cat in there?")
    server << "Fuck you, asshole";
  else
    server << "I can't hear you.";
}

int main()
{
  ErrorCodes errorCode = ErrorCodes::OK;
  Server server(12000);
  auto serverConnection = server.accept();
  Connection connection(IPendpoint(IPaddress("127.0.0.1"), 12000, TransportProtocol::TCP));
  connection << "You got a dead cat in there?";
  handleConnection(serverConnection.get());

  string message;
  connection >> message;
  cout << "Client received: " << message;  

  return static_cast<int>(errorCode);
}