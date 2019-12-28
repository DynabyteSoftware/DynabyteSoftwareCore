#pragma once
#include "CoreExports.h"
#include "AddressFamily.h"
#include "ICloneable.h"
#include "IEquatable.h"
#include <cstddef>
#include <string>
#include <vector>

namespace DynabyteSoftware
{
  namespace Networking
  {
    namespace Internal
    {
      class IIPaddress
        : public virtual IEquatable<IIPaddress>, public virtual ICloneable<IIPaddress>
      {
      public:
        #pragma region Observers
        virtual AddressFamily getAddressFamily() const = 0;
        virtual std::vector<std::byte> getAddressBytes() const = 0;
        virtual std::string toString() const = 0;
        #pragma endregion

        #pragma region IEquatable
        virtual bool operator==(const IIPaddress& other) const override;
        #pragma endregion
      };
    }
  }
}