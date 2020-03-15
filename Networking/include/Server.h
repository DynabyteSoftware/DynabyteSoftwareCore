#pragma once
#include "Internal/IServer.h"
#include "Connection.h"

namespace DynabyteSoftware
{
  namespace Networking
  {
    class Server : public virtual Internal::IServer
    {
    public:
      #pragma region Constructors
      Server(uint32_t port, TransportProtocol protocol = TransportProtocol::TCP);
      #pragma endregion

      #pragma region IServer
      inline virtual std::future<Connection> accept() override;
      #pragma endregion
    private:
      #pragma region Variables
      std::unique_ptr<Internal::IServer> _implementation;
      #pragma endregion
    };
  }
}