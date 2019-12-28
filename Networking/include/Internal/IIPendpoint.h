#pragma once
#include <cstdint>
#include <string>

namespace DynabyteSoftware
{
  namespace Networking
  {
    namespace Internal
    {
      class IIPaddress;

      class IIPendpoint
        : protected ICloneable<IIPendpoint>
      {
      public:
        #pragma region Constants
        static constexpr uint32_t MaxPort = 0x0000FFFF;
        #pragma endregion

        #pragma region Modifiers
        void setAddress(const IIPaddress& ipAddress) = 0;
        void setPort(uint32_t port) = 0;
        #pragma endregion

        #pragma region Observers
        const IIPaddress& getAddress() const = 0;
        uint32_t getPort() const = 0;
        std::string toString() const = 0;
        #pragma endregion
      };
    }
  }
}