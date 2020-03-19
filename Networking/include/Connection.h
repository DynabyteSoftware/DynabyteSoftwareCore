#pragma once
#include "Internal/IConnection.h"
#include "Internal/IServer.h"
#include "IPendpoint.h"
#include "Key.h"

namespace DynabyteSoftware
{
  namespace Networking
  {
    class Connection : public virtual Internal::IConnection
    {
    public:
      #pragma region Constructors
      Connection();
      Connection(const IPendpoint& endpoint);
      Connection(const std::shared_ptr<Internal::IConnection>& implementation, const Key<Internal::IServer>&);
      //Connection(const Connection& original);
      Connection(Connection&& old);
      #pragma endregion

      #pragma region Operator
      Connection& operator=(Connection&& old);
      #pragma endregion
    private:
      #pragma region Variables
      std::shared_ptr<Internal::IConnection> _implementation;
      #pragma endregion
    };
  }
}