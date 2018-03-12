/***********************************************************************************************************************
* @file ContainerWrapper.h
* @author Rod Leonard
* @version 0.0.1
* @date 2018/03/11
* @copyright Dynabyte Software LLC, licensed under LGPL 3.0 so later
* @brief Header file for DynabyteSoftware's ContainerWrapper class
**********************************************************************************************************************/

#include "IEnumerable.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename IteratorType>
    class IteratorWrapper
      : public ForwardIterator<typename IteratorType::value_type, IteratorWrapper<IteratorType>>
    {
    public:
      IteratorWrapper(IteratorType& iterator)
        : _iterator(iterator)
      {
      }

      #pragma region ForwardIterator
      virtual IteratorWrapper& operator++() override
      {
        ++_iterator;
        return *this;
      }

      virtual IteratorWrapper& operator=(const IteratorWrapper& rhs) override
      {
        _iterator = rhs._iterator;
        return *this;
      }

      virtual reference operator*() const override
      {
        return *_iterator;
      }

      virtual pointer operator->() const override
      {
        return _iterator.operator->();
      }

      virtual bool operator==(const IteratorWrapper& rhs) const override
      {
        return _iterator == rhs._iterator;
      }
      #pragma endregion
    private:
      IteratorType _iterator;
    };

    template<typename Container>
    class ContainerWrapper : public IEnumerable<IteratorWrapper<typename Container::iterator>>
    {
    public:
      ContainerWrapper(Container& container)
        : _container(container)
      {
      }

      virtual iterator begin() override
      {
        return iterator(_container.begin());
      }

      virtual iterator end() override
      {
        return iterator(_container.end());
      }
    private:
      Container& _container;
    };

    template<typename Container>
    ContainerWrapper<Container> make_container_wrapper(Container& container)
    {
      return ContainerWrapper<Container>(container);
    }
  }
}