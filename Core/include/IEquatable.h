#pragma once

namespace DynabyteSoftware
{
  template<typename T>
  class IEquatable
  {
  public:
    #pragma region Destructor
    inline virtual ~IEquatable() {};
    #pragma endregion

    #pragma region Observers
    virtual bool operator==(const T& other) const = 0;
    #pragma endregion

    #pragma region Operators
    bool operator!=(const T& other) const
    {
      return !operator==(other);
    }
    #pragma endregion
  };
}