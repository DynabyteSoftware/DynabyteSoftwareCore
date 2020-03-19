#pragma once
#include "Key.h"
#include "TransportProtocol.h"
#include<future>

namespace DynabyteSoftware
{
  namespace Networking
  {
    class Connection;
    namespace Internal
    {
      class IServer
      {
      public:
        #pragma region Modifiers
        virtual std::future<Connection> accept() = 0;
        #pragma endregion
      protected:
        #pragma region AccessKey
        inline static const Key<IServer>& key()
        {
          static const Key<IServer> _key;
          return _key;
        }
        #pragma endregion
      };
    }
  }
}