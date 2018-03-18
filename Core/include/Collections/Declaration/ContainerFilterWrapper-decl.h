/***********************************************************************************************************************
* @file ContainerFilterWrapper-decl.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/14
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ContainerIteratorWrapper declaration class
**********************************************************************************************************************/
#pragma once
#include "Collections/FilterEnumerator.h"
#include "Collections/Declaration/IEnumerable-decl.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    /******************************************************************************************************************
     * @class ContainerFilterWrapper
     * @ingroup DynabyteSoftware::Collections
     * @brief Wraps an existing container into one that filters contents based on a given filter
     * @see IEnumerable
     * @see FilterEnumerator
     * @details
     * Wraps an existing container into one that uses filter iterators so that only values that satisfy the filter
     * condition are iterated through
     *****************************************************************************************************************/
    template<typename Container>
    class ContainerFilterWrapper
      : public IEnumerable<ContainerFilterWrapper<Container>, FilterEnumerator<typename Container::iterator>>
    {
    public:
      /**
       * Constructor for a ContainerFilterWrapper object
       *
       * @param container[in,out] The container being wrapped
       * @param filter[in] A function that takes in a constant reference to the value in the container and returns
       *                   true if the value should be returned, false if the value should be skipped
       **/
      ContainerFilterWrapper(Container& container, const typename iterator::filter_function& filter);

      /**
       * @return iterator to the beginning of the filtered sequence
       **/
      virtual iterator begin() override;
      /**
       * @return iterator past the end of the sequence
       **/
      virtual iterator end() override;
    private:
      Container& _container;
      typename iterator::filter_function _filter;
    };
  }
}