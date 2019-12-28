#pragma once

namespace DynabyteSoftware
{
  template<typename T>
  class IAssignable
  {
  public:
    #pragma region Destructor
    inline virtual ~IAssignable() {};
    #pragma endregion

    #pragma region Modifiers
    virtual T& operator=(const T& rhs) = 0;
    virtual T& operator=(T&& rhs) = 0;
    #pragma endregion
  };
}