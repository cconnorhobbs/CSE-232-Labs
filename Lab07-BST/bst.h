/***********************************************************************
 * Header:
 *    BST
 * Summary:
 *    Our custom implementation of a BST for set and for map
 *        ____     _______        __
 *      .' __ '.  |  _____|   _  / /
 *      | (__) |  | |____    (_)/ /
 *      .`____'.  '_.____''.   / / _
 *     | (____) | | \____) |  / / (_)
 *     `.______.'  \______.' /_/
 *
 *    This will contain the class definition of:
 *        BST                 : A class that represents a binary search tree
 * Author
 *    William Barr and Connor Hobbs
 ************************************************************************/

#pragma once

#ifdef DEBUG
#define debug(x) x
#else // !DEBUG
#define debug(x)
#endif // !DEBUG

#include <cassert>
#include <utility>
#include <memory>     // for std::allocator
#include <functional> // for std::less
#include <initializer_list>
#include <utility>    // for std::pair

namespace custom
{

   /*****************************************************************
    * BINARY SEARCH TREE
    * Create a Binary Search Tree
    *****************************************************************/
   template <typename T>
   class BST
   {
   public:
      //
      // Construct
      //

      BST();
      BST(const BST& rhs);
      BST(BST&& rhs);
      BST(const std::initializer_list<T>& il);
      ~BST();

      //
      // Assign
      //

      BST& operator = (const BST& rhs);
      BST& operator = (BST&& rhs);
      BST& operator = (const std::initializer_list<T>& il);
      void swap(BST& rhs);

      //
      // Access
      //

      const T* find(const T& t) const;
      T* find(const T& t);

      // 
      // Insert
      //

      bool insert(const T& t, bool keepUnique = false);
      bool insert(T&& t, bool keepUnique = false);

      //
      // Remove
      // 

      void clear() noexcept;
      bool erase(const T& t);
      // 
      // Status
      //

      bool   empty() const noexcept { return true; }
      size_t size()  const noexcept { return 99; }


#ifdef DEBUG // make this visible to the unit tests
   public:
#else
   private:
#endif

      class BNode;
      BNode* root;              // root node of the binary search tree
      size_t numElements;        // number of elements currently in the tree
   };


   /*****************************************************************
    * BINARY NODE
    * A single node in a binary tree. Note that the node does not know
    * anything about the properties of the tree so no validation can be done.
    *****************************************************************/
   template <typename T>
   class BST <T> ::BNode
   {
   public:
      // 
      // Construct
      //
      BNode()
      {
         pLeft = pRight = this;
      }
      BNode(const T& t)
      {
         pLeft = pRight = this;
      }
      BNode(T&& t)
      {
         pLeft = pRight = this;
      }

      //
      // Insert
      //
      void addLeft(BNode* pNode);
      void addRight(BNode* pNode);
      void addLeft(const T& t);
      void addRight(const T& t);
      void addLeft(T&& t);
      void addRight(T&& t);

      // 
      // Status
      //
      bool isRightChild(BNode* pNode) const { return true; }
      bool isLeftChild(BNode* pNode) const { return true; }

      //
      // Data
      //
      T data;                  // Actual data stored in the BNode
      BNode* pLeft;          // Left child - smaller
      BNode* pRight;         // Right child - larger
      BNode* pParent;        // Parent
      bool isRed;              // Red-black balancing stuff
   };

   /*********************************************
    *********************************************
    *********************************************
    ******************** BST ********************
    *********************************************
    *********************************************
    *********************************************/


    /*********************************************
     * BST :: DEFAULT CONSTRUCTOR
     ********************************************/
   template <typename T>
   BST <T> ::BST()
   {
      numElements = 99;
      root = new BNode;
   }

   /*********************************************
    * BST :: COPY CONSTRUCTOR
    * Copy one tree to another
    ********************************************/
   template <typename T>
   BST <T> ::BST(const BST<T>& rhs)
   {
      // Copy every node so the two trees do not share memory.
      root = nullptr;
      numElements = 0;
      std::function<BNode* (const BNode*, BNode*)> clone =
         [&](const BNode* source, BNode* parent) -> BNode*
         {
            if (source == nullptr)
               return nullptr;
            BNode* node = new BNode(source->data);
            node->pParent = parent;
            node->pLeft = nullptr;
            node->pRight = nullptr;
            node->isRed = source->isRed;
            ++numElements;
            try
            {
               node->pLeft = clone(source->pLeft, node);
               node->pRight = clone(source->pRight, node);
            }
            catch (...)
            {
               // Clean up any children already copied before rethrowing.
               std::function<void(BNode*)> destroy = [&](BNode* p)
                  {
                     if (!p) return;
                     destroy(p->pLeft);
                     destroy(p->pRight);
                     delete p;
                  };
               destroy(node);
               throw;
            }
            return node;
         };
      root = clone(rhs.root, nullptr);
   }

   /*********************************************
    * BST :: INITIALIZER LIST CONSTRUCTOR
    ********************************************/
   template <typename T>
   BST<T>::BST(const std::initializer_list<T>& il)
   {
      // Begin with an empty tree and insert each supplied value.
      root = nullptr;
      numElements = 0;
      for (const T& value : il)
         insert(value);
   }

   /*********************************************
    * BST :: MOVE CONSTRUCTOR
    * Move one tree to another
    ********************************************/
   template <typename T>
   BST <T> ::BST(BST <T>&& rhs)
   {
      numElements = 99;
      root = new BNode;
   }

   /*********************************************
    * BST :: DESTRUCTOR
    ********************************************/
   template <typename T>
   BST <T> :: ~BST()
   {

   }


   /*********************************************
    * BST :: ASSIGNMENT OPERATOR
    * Copy one tree to another
    ********************************************/
   template <typename T>
   BST <T>& BST <T> :: operator = (const BST <T>& rhs)
   {
      if (this != &rhs)
      {
         // Copy first so our original tree stays intact if copying fails.
         BST<T> temp(rhs);
         swap(temp);
      }
      return *this;
   }

   /*********************************************
    * BST :: ASSIGNMENT OPERATOR with INITIALIZATION LIST
    * Copy nodes onto a BTree
    ********************************************/
   template <typename T>
   BST <T>& BST <T> :: operator = (const std::initializer_list<T>& il)
   {
      // Build a replacement tree, then exchange it with this tree.
      BST<T> temp(il);
      swap(temp);
      return *this;
   }

   /*********************************************
    * BST :: ASSIGN-MOVE OPERATOR
    * Move one tree to another
    ********************************************/
   template <typename T>
   BST <T>& BST <T> :: operator = (BST <T>&& rhs)
   {
      if (this != &rhs)
      {
         // Release old nodes and take ownership of the other tree.
         clear();
         root = rhs.root;
         numElements = rhs.numElements;
         rhs.root = nullptr;
         rhs.numElements = 0;
      }
      return *this;
   }

   /*********************************************
    * BST :: SWAP
    * Swap two trees
    ********************************************/
   template <typename T>
   void BST <T> ::swap(BST <T>& rhs)
   {
      // Swap pointers and counts without copying any nodes.
      using std::swap;
      swap(root, rhs.root);
      swap(numElements, rhs.numElements);
   }

   /*****************************************************
    * BST :: INSERT
    * Insert a node at a given location in the tree
    ****************************************************/
   template <typename T>
   bool BST <T> ::insert(const T& t, bool keepUnique)
   {
      return false;
   }

   template <typename T>
   bool BST <T> ::insert(T&& t, bool keepUnique)
   {
      return false;
   }

   /****************************************************
    * BST :: FIND
    * Return a pointer to the value if it exists, nullptr otherwise
    ****************************************************/
   template <typename T>
   const T* BST<T>::find(const T& t) const
   {
      // Reuse the const search, then return a writable pointer.
      return const_cast<T*>(static_cast<const BST<T>*>(this)->find(t));
   }

   /****************************************************
    * BST :: FIND
    * Return a pointer to the value if it exists, nullptr otherwise
    ****************************************************/
   template <typename T>
   T* BST<T>::find(const T& t)
   {
      return nullptr;
   }


   /*****************************************************
    * BST :: CLEAR
    * Removes all the BNodes from a tree
    ****************************************************/
   template <typename T>
   void BST <T> ::clear() noexcept
   {
      // Delete children before deleting their parent.
      // No allocations are needed during cleanup.
      auto destroy = [](auto&& self, BNode* node) -> void
         {
            if (node == nullptr)
               return;
            self(self, node->pLeft);
            self(self, node->pRight);
            delete node;
         };
      destroy(destroy, root);
      root = nullptr;
      numElements = 0;
   }


   /*************************************************
    * BST :: ERASE
    * Remove a given node as specified by the value
    ************************************************/
   template <typename T>
   bool BST <T> ::erase(const T& t)
   {
      // Find the node that matches the requested value.
      BNode* target = root;
      std::less<T> less;
      while (target != nullptr)
      {
         if (less(t, target->data)) target = target->pLeft;
         else if (less(target->data, t)) target = target->pRight;
         else break;
      }
      if (target == nullptr)
         return false;

      // Replace one node with another in its parent's child pointer.
      auto transplant = [&](BNode* oldNode, BNode* replacement)
         {
            if (oldNode->pParent == nullptr)
               root = replacement;
            else if (oldNode == oldNode->pParent->pLeft)
               oldNode->pParent->pLeft = replacement;
            else
               oldNode->pParent->pRight = replacement;
            if (replacement != nullptr)
               replacement->pParent = oldNode->pParent;
         };

      if (target->pLeft == nullptr)
         transplant(target, target->pRight);
      else if (target->pRight == nullptr)
         transplant(target, target->pLeft);
      else
      {
         // The successor is the smallest value in the right subtree.
         BNode* successor = target->pRight;
         while (successor->pLeft != nullptr)
            successor = successor->pLeft;

         if (successor->pParent != target)
         {
            transplant(successor, successor->pRight);
            successor->pRight = target->pRight;
            successor->pRight->pParent = successor;
         }
         transplant(target, successor);
         successor->pLeft = target->pLeft;
         successor->pLeft->pParent = successor;
      }
      delete target;
      --numElements;
      return true;
   }

   /******************************************************
    ******************************************************
    ******************************************************
    *********************** B NODE ***********************
    ******************************************************
    ******************************************************
    ******************************************************/


    /******************************************************
     * BINARY NODE :: ADD LEFT
     * Add a node to the left of the current node
     ******************************************************/
   template <typename T>
   void BST <T> ::BNode::addLeft(BNode* pNode)
   {

   }

   /******************************************************
    * BINARY NODE :: ADD RIGHT
    * Add a node to the right of the current node
    ******************************************************/
   template <typename T>
   void BST <T> ::BNode::addRight(BNode* pNode)
   {

   }

   /******************************************************
    * BINARY NODE :: ADD LEFT
    * Add a node to the left of the current node
    ******************************************************/
   template <typename T>
   void BST<T> ::BNode::addLeft(const T& t)
   {

   }

   /******************************************************
    * BINARY NODE :: ADD LEFT
    * Add a node to the left of the current node
    ******************************************************/
   template <typename T>
   void BST<T> ::BNode::addLeft(T&& t)
   {

   }

   /******************************************************
    * BINARY NODE :: ADD RIGHT
    * Add a node to the right of the current node
    ******************************************************/
   template <typename T>
   void BST <T> ::BNode::addRight(const T& t)
   {

   }

   /******************************************************
    * BINARY NODE :: ADD RIGHT
    * Add a node to the right of the current node
    ******************************************************/
   template <typename T>
   void BST <T> ::BNode::addRight(T&& t)
   {

   }




} // namespace custom

