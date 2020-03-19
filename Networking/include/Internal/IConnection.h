#pragma once
#include <string>

namespace DynabyteSoftware
{
  namespace Networking
  {
    namespace Internal
    {
      class IConnection
      {
      public:
        #pragma region Destructors
        inline virtual ~IConnection() {};
        #pragma endregion

        #pragma region Operators
        virtual IConnection& operator<<(const std::string& message) = 0;
        virtual IConnection& operator>>(std::string& message) = 0;
        #pragma endregion
      };
    }
  }
}