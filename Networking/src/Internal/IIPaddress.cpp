#include "Internal/IIPaddress.h"

using namespace DynabyteSoftware::Networking::Internal;
using namespace std;

#pragma region IEquatable
bool IIPaddress::operator==(const IIPaddress& other) const
{
  auto bytes = getAddressBytes();
  auto otherBytes = getAddressBytes();
  if (bytes.size() != otherBytes.size())
    return false;

  for (size_t byteIndex = 0; byteIndex < bytes.size(); ++byteIndex)
    if (bytes[byteIndex] != otherBytes[byteIndex])
      return false;

  return true;
}
#pragma endregion