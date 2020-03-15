#pragma once

namespace DynabyteSoftware
{
  #pragma region Variant Visitor
  template<typename... Ts> struct overloaded : Ts... {using Ts::operator()...; };
  template<typename... Ts> overloaded(Ts...)->overloaded<Ts...>;
  #pragma endregion
}