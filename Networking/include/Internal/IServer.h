#pragma once
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
      };
    }
  }
}