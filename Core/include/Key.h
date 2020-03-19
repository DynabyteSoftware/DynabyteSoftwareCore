#pragma once

namespace DynabyteSoftware
{
  template<typename Owner>
  class Key
  {
    friend Owner;
    inline Key() {};
    Key(const Key&) = delete;
  };
}