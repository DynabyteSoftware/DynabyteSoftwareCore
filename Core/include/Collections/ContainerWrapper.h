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
    #pragma region Iterator Wrapper
    /******************************************************************************************************************
    * @class IteratorWrapper
    * @ingroup DynabyteSoftware::Collections
    * @brief Wraps an existing iterator into one that inherits from an IIterator template
    * @see ForwardIterator
    * @details
    * Wraps an existing iterator into one that inheritis from the provided template that guarantees certain
    * functionality
    ******************************************************************************************************************/
    template<typename IteratorType>
    class IteratorWrapper
      : public ForwardIterator<typename IteratorType::value_type, IteratorWrapper<IteratorType>>
    {
    public:
      #pragma region Type Definitions
      typedef typename ForwardIterator<typename IteratorType::value_type,
                                       IteratorWrapper<IteratorType>>::reference reference;
      typedef typename ForwardIterator<typename IteratorType::value_type,
                                       IteratorWrapper<IteratorType>>::pointer pointer;
      #pragma endregion
      
      #pragma region Constructor
      /**
       * Constructor for an iterator wrapper
       * @param iterator The iterator being wrapped
       **/
      IteratorWrapper(const IteratorType& iterator)
        : _iterator(iterator)
      {
      }
      #pragma endregion

      #pragma region ForwardIterator
      /**
       * Advances the iterator
       * @return A reference to this iterator wrapper after the container iterator has been advanced
       **/
      virtual IteratorWrapper& operator++() override
      {
        ++_iterator;
        return *this;
      }

      /**
       * Assigns another iterator to this one
       * @return A reference to this iterator, after it has been assigned to another
       **/
      virtual IteratorWrapper& operator=(const IteratorWrapper& rhs) override
      {
        _iterator = rhs._iterator;
        return *this;
      }

      /**
       * Derefences this iterator
       * @return A reference to the value being pointed to by the iterator
       **/
      virtual reference operator*() const override
      {
        return *_iterator;
      }

      /**
       * Retrieves address of value
       * @return a pointer to the value being pointed to by the iterator
       **/
      virtual pointer operator->() const override
      {
        return _iterator.operator->();
      }

      /**
      * Compares this iterator wrapper to another
      * @return true if the container iterators match
      **/
      virtual bool operator==(const IteratorWrapper& rhs) const override
      {
        return _iterator == rhs._iterator;
      }
      #pragma endregion
    private:
      IteratorType _iterator;
    };
    #pragma endregion

    #pragma region ContainerWrapper
    /******************************************************************************************************************
    * @class ContainerFilterWrapper
    * @ingroup DynabyteSoftware::Collections
    * @brief Wraps an existing container into one that inhertis from IEnumerable and provides additional functionality
    * @see IEnumerable
    * @see IteratorWrapper
    * @details
    * Wraps an existing container into one that inherits from IEnumerable and provides additional functionality
    * @note Is only valid for as long as container passed in is valid. This container does not make a copy of the 
    *       contents of the passed container
    *****************************************************************************************************************/
    template<typename Container>
    class ContainerWrapper
      : public IEnumerable<ContainerWrapper<Container>, IteratorWrapper<typename Container::iterator>>
    {
    public:
      #pragma region Type Definitions
      typedef IteratorWrapper<typename Container::iterator> iterator;
      #pragma endregion
      
      #pragma region Constructor
      /**
       * Constructor to a ContainerWrapper object
       *
       * @param container[in,out] The container being wrapped
       **/
      ContainerWrapper(Container& container)
        : _container(container)
      {
      }
      #pragma endregion

      #pragma region IEnumerable
      /**
       * @return An iterator to the beginning of the sequence
       **/
      virtual iterator begin() override
      {
        return iterator(_container.begin());
      }

      /**
       * @return an iterator past the end of the sequence
       **/
      virtual iterator end() override
      {
        return iterator(_container.end());
      }
      #pragma endregion
    private:
      Container& _container;
    };
    #pragma endregion

    template<typename Container>
    ContainerWrapper<Container> make_container_wrapper(Container& container)
    {
      return ContainerWrapper<Container>(container);
    }
  }
}
