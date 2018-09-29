//#pragma once
//#include "Collections/Enumerator.h"
//#include "Collections/Iterator/IForwardIterator.h"
//#include <functional>
//
//namespace DynabyteSoftware
//{
//  namespace Collections
//  {
//    namespace Wrappers
//    {
//      template<typename T>
//      class FilterIterator final : public Iterators::IForwardIterator<T>
//      {
//      public:
//        #pragma region Constructors
//        FilterIterator(const Enumerator<T>& enumerator)
//          : _enumerator(enumerator)
//        {
//        }
//        #pragma endregion
//
//        #pragma region IForwardIterator
//        #pragma endregion
//      private:
//        Enumerator<T> _enumerator;
//        std::function<bool()
//      };
//    }
//  }
//}