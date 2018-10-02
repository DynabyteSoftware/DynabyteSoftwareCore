#pragma once
#include "Collections/TemplateDeclarations/IEnumerable-decl.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    namespace Wrappers
    {
      template<typename T>
      class EnumeratorWrapper : public IEnumerable<T>
      {
      public:
        #pragma region Constructors
        EnumeratorWrapper(const Enumerator<T>& enumerator)
          : _enumerator(enumerator)
        {
        }
        #pragma endregion

        #pragma region IEnumerable
        virtual Enumerator<T> getEnumerator() const override
        {
          return _enumerator;
        }
        #pragma endregion
      private:
        #pragma region Variables
        Enumerator<T> _enumerator;
        #pragma endregion
      };
    }
  }
}