#pragma once
#include "Collections/TemplateDeclarations/IEnumerable-decl.h"

namespace DynabyteSoftware
{
  namespace Collections
  {
    template<typename T>
    class BinaryTree : public IEnumerable<T>
    {
    public:
      #pragma region Modifiers
      void insert(std::conditional_t<std::is_reference_v<T> || std::is_pointer_v<T>,
                                     T, std::add_lvalue_reference_t< std::add_const_t<T> > > value)
      {
        insert(_root, value);
      }
      #pragma endregion

      #pragma region IEnumerable
      virtual Enumerator<T> getEnumerator() const override
      {
        return make_enumerator(InOrderDepthFirstIterator<T>(_root),
                               InOrderDepthFirstIterator<T>(std::shared_ptr<Node>{}));
      }
      #pragma endregion
    private:
      #pragma region Types
      struct Node
      {
        Node(T value)
          : Value(value)
        {
        }

        T Value;
        std::weak_ptr<Node> Parent;
        std::shared_ptr<Node> LeftChild;
        std::shared_ptr<Node> RightChild;
      };
      
      template<typename U>
      class InOrderDepthFirstIterator : public Iterators::IIterator<U>
      {
      public:
        #pragma region Constructors
        InOrderDepthFirstIterator(const std::weak_ptr<Node>& root)
          : _root(root)
        {
          if (!_root.expired())
            initializeCurrent(_root.lock());
        }
        #pragma endregion

        #pragma region IIterator
        virtual InOrderDepthFirstIterator<U>& operator++() override
        {
          if(!_current.expired())
          {
            auto current = _current.lock();
            if (current->RightChild)
            {
              current = current->RightChild;
              while (current->LeftChild)
                current = current->LeftChild;
              _current = current;
            }
            else
            {
              if (current->Parent.expired())
                _current.reset();
              else
              {
                auto parent = current->Parent.lock();
                if (parent->RightChild == current)
                {
                  if (parent->Parent.expired())
                    _current.reset();
                  else
                    _current = parent->Parent.lock();
                }
                else
                  _current = parent;
              }
            }
          }
          return *this;
        }

        virtual InOrderDepthFirstIterator<U>& operator++(int) override
        {
          return operator++();
        }

        virtual bool operator==(const IIterator<U>& rhs) const override
        {
          if (const auto* rhsPtr = dynamic_cast<const InOrderDepthFirstIterator<U>*>(&rhs))
          {
            if (_current.expired())
              return rhsPtr->_current.expired();

            if(!rhsPtr->_current.expired())
              return _current.lock() == rhsPtr->_current.lock();
          }
          return false;
        }

        virtual typename IIterator<U>::reference operator*() const override
        {
          if (_current.expired())
            THROW(Exception, "Iterator does not point to a current object")
          return _current.lock()->Value;
        }

        virtual typename IIterator<U>::pointer operator->() const override
        {
          if (_current.expired())
            THROW(Exception, "Iterator does not point to a current object")
          return &_current.lock()->Value;
        }

        virtual std::unique_ptr< IIterator<U> > clone() const override
        {
          auto iteratorClone = std::make_unique<InOrderDepthFirstIterator>(_root);
          iteratorClone->_current = _current;
          return iteratorClone;
        }

        virtual std::unique_ptr< IIterator< std::add_const_t<U> > > getConst() const override
        {
          return make_unique< InOrderDepthFirstIterator< std::add_const_t<U> > >(_root);
        }

        virtual void assign(const IIterator<U>& rhs) override
        {
          if (const auto* rhsPtr = dynamic_cast<const InOrderDepthFirstIterator<U>*>(&rhs))
          {
            _root = rhsPtr->_root;
            _current = rhsPtr->_current;
          }
        }
        #pragma endregion
      private:
        #pragma region Variables
        std::weak_ptr<Node> _root;
        std::weak_ptr<Node> _current;
        #pragma endregion

        #pragma region Functions
        void initializeCurrent(std::shared_ptr<Node>& proposedCurrent)
        {
          if(proposedCurrent)
          {
            if (proposedCurrent->LeftChild)
              initializeCurrent(proposedCurrent->LeftChild);
            else
              _current = proposedCurrent;
          }
        }
        #pragma endregion
      };   
      #pragma endregion

      #pragma region Variables
      std::shared_ptr<Node> _root;
      #pragma endregion

      #pragma region Modifiers
      void insert(std::shared_ptr<Node>& parent,
                  std::conditional_t<std::is_reference_v<T> || std::is_pointer_v<T>,
                                     T, std::add_lvalue_reference_t< std::add_const_t<T> > > value)
      {
        if(parent)
        {
          if (value < parent->Value)
          {
            insert(parent->LeftChild, value);
            if(parent->LeftChild->Parent.expired())
              parent->LeftChild->Parent = parent;
          }
          else if (value > parent->Value)
          {
            insert(parent->RightChild, value);
            if(parent->RightChild->Parent.expired())
              parent->RightChild->Parent = parent;
          }
          else
          {
            std::shared_ptr<Node> newNode(new Node(value));
            newNode->Parent = parent->Parent;
            newNode->RightChild = std::move(parent->RightChild);
            newNode->LeftChild = std::move(parent);
            newNode->LeftChild->Parent = std::move(newNode);
          }
        }
        else
        {
          std::shared_ptr<Node> newNode(new Node(value));
          parent = newNode;
        }
      }
      #pragma endregion
    };
  }
}