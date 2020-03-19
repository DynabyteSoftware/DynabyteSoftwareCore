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
      NETWORKING_EXPORT Server(uint16_t port);
      #pragma endregion

      #pragma region IServer
      NETWORKING_EXPORT inline virtual std::future<Connection> accept() override;
      #pragma endregion
    private:
      #pragma region Variables
      std::unique_ptr<Internal::IServer> _implementation;
      #pragma endregion
    };
  }
}