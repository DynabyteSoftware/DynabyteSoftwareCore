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
      NETWORKING_EXPORT Connection();
      NETWORKING_EXPORT Connection(const IPendpoint& endpoint);
      NETWORKING_EXPORT Connection(const std::shared_ptr<Internal::IConnection>& implementation,
                                   const Key<Internal::IServer>&);
      NETWORKING_EXPORT Connection(Connection&& old);
      #pragma endregion

      #pragma region Operator
      NETWORKING_EXPORT Connection& operator=(Connection&& old);
      #pragma endregion

      #pragma region IConnection
      virtual Connection& operator<<(const std::string& message) override;
      virtual Connection& operator>>(std::string& message) override;
      #pragma endregion
    private:
      #pragma region Variables
      std::shared_ptr<Internal::IConnection> _implementation;
      #pragma endregion
    };
  }
}