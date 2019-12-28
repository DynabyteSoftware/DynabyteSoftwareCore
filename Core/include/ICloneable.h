#pragma once
#include <memory>

namespace DynabyteSoftware
{
  template<typename T>
  class ICloneable
  {
  public:
    #pragma region Destructor
    inline virtual ~ICloneable() {};
    #pragma endregion

    #pragma region Observers
    virtual std::unique_ptr<T> clone() const = 0;
    #pragma endregion
  };
}