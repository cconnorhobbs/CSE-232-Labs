/***********************************************************************
 * Header:
 *    BINARY NODE
 * Summary:
 *    One node in a binary tree (and the functions to support them).
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        BNode         : A class representing a BNode
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <iostream>  // for OFSTREAM
#include <cassert>
#include <utility> // std::move and std::swap

 /*****************************************************************
  * BNODE
  * A single node in a binary tree.  Note that the node does not know
  * anything about the properties of the tree so no validation can be done.
  *****************************************************************/
template <class T>
class BNode
{
public:
   // 
   // Construct
   //
   BNode() : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data()
   {
      // Start with no children or parent.
      pLeft = pRight = pParent = nullptr;
   }
   BNode(const T& t) : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(t)
   {
      // Copy the value into this node.
      pLeft = pRight = pParent = nullptr;
   }
   BNode(T&& t) : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(std::move(t))
   {
      // Move the value into this node.
      pLeft = pRight = pParent = nullptr;
   }

   //
   // Data
   //
   BNode <T>* pLeft;
   BNode <T>* pRight;
   BNode <T>* pParent;
   T data;
};

/*******************************************************************
 * SIZE BTREE
 * Return the size of a b-tree under the current node
 *******************************************************************/
template <class T>
inline size_t size(const BNode <T>* p)
{
   // Count this node and everything below it.
   if (p == nullptr) return 0;
   return 1 + size(p->pLeft) + size(p->pRight);
}


/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft(BNode <T>* pNode, BNode <T>* pAdd)
{
   if (pNode == nullptr) return;
   // Attach the supplied subtree and update its parent.
   pNode->pLeft = pAdd;
   if (pAdd != nullptr) pAdd->pParent = pNode;
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
inline void addRight(BNode <T>* pNode, BNode <T>* pAdd)
{
   if (pNode == nullptr) return;
   // Attach the supplied subtree and update its parent.
   pNode->pRight = pAdd;
   if (pAdd != nullptr) pAdd->pParent = pNode;
}

/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft(BNode <T>* pNode, const T& t)
{
   if (pNode == nullptr) return;
   // Copy the value into a newly allocated left child.
   addLeft(pNode, new BNode<T>(t));
}

template <class T>
inline void addLeft(BNode <T>* pNode, T&& t)
{
   if (pNode == nullptr) return;
   // Move the value into a newly allocated left child.
   addLeft(pNode, new BNode<T>(std::move(t)));
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
void addRight(BNode <T>* pNode, const T& t)
{
   if (pNode == nullptr) return;
   // Copy the value into a newly allocated right child.
   addRight(pNode, new BNode<T>(t));
}

template <class T>
void addRight(BNode <T>* pNode, T&& t)
{
   if (pNode == nullptr) return;
   // Move the value into a newly allocated right child.
   addRight(pNode, new BNode<T>(std::move(t)));
}

/*****************************************************
 * DELETE BINARY TREE
 * Delete all the nodes below pThis including pThis
 * using postfix traverse: LRV
 ****************************************************/
template <class T>
void clear(BNode <T>*& pThis)
{
   if (pThis == nullptr) return;
   // Delete children first, then delete this node (postorder).
   clear(pThis->pLeft);
   clear(pThis->pRight);
   delete pThis;
   pThis = nullptr;
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(BNode <T>*& pLHS, BNode <T>*& pRHS)
{
   // Swap root pointers without copying the trees.
   std::swap(pLHS, pRHS);
}

/**********************************************
 * COPY BINARY TREE
 * Copy pSrc->pRight to pDest->pRight and
 * pSrc->pLeft onto pDest->pLeft
 *********************************************/
template <class T>
BNode <T>* copy(const BNode <T>* pSrc)
{
   if (pSrc == nullptr) return nullptr;
   // Create an independent node and recursively copy its children.
   BNode<T>* result = new BNode<T>(pSrc->data);
   addLeft(result, copy(pSrc->pLeft));
   addRight(result, copy(pSrc->pRight));
   return result;
}

/**********************************************
 * assign
 * copy the values from pSrc onto pDest preserving
 * as many of the nodes as possible.
 *********************************************/
template <class T>
void assign(BNode <T>*& pDest, const BNode <T>* pSrc)
{
   // Reuse existing nodes whenever both trees have a node here.
   if (pSrc == nullptr)
   {
      clear(pDest);
      return;
   }
   if (pDest == nullptr)
   {
      pDest = copy(pSrc);
      return;
   }
   pDest->data = pSrc->data;
   assign(pDest->pLeft, pSrc->pLeft);
   assign(pDest->pRight, pSrc->pRight);
   // Children created by assign need their parent pointers set.
   if (pDest->pLeft != nullptr) pDest->pLeft->pParent = pDest;
   if (pDest->pRight != nullptr) pDest->pRight->pParent = pDest;
}
