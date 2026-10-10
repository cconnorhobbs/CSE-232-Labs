/***********************************************************************
 * Header:
 *    NODE
 * Summary:
 *    One node in a linked list (and the functions to support them).
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        Node         : A class representing a Node
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    William Barr and Connor Hobbs
 ************************************************************************/

#pragma once

#include <cassert>     // for ASSERT
#include <iostream>    // for NULL
#include <utility>     // for std::move

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <class T>
class Node
{
public:

   //
   // Construct
   //

   // Default constructor that creates an empty node
   Node() : data(), pNext(nullptr), pPrev(nullptr)
   {
   }

   // Constructor that copies the given data into a new node
   Node(const T& data) : data(data), pNext(nullptr), pPrev(nullptr)
   {
   }

   // Constructor that moves the given data into a new node
   Node(T&& data) : data(std::move(data)), pNext(nullptr), pPrev(nullptr)
   {
   }


   //
   // Member variables
   //

   T data;                 // user data
   Node <T> * pNext;       // pointer to next node
   Node <T> * pPrev;       // pointer to previous node
};

/***********************************************
 * COPY
 * Copy the list from the pSource and return
 * the new list
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline Node <T> * copy(const Node <T> * pSource) 
{
   return new Node<T>;
}

/***********************************************
 * Assign
 * Copy the values from pSource into pDestination
 * reusing the nodes already created in pDestination if possible.
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline void assign(Node <T> * & pDestination, const Node <T> * pSource)
{
   
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(Node <T>* &pLHS, Node <T>* &pRHS)
{

}

/***********************************************
 * REMOVE
 * Remove the node pSource in the linked list
 *   INPUT  : the node to be removed
 *   OUTPUT : the pointer to the parent node
 *   COST   : O(1)
 **********************************************/
template <class T>
inline Node<T>* remove(const Node<T>* pRemove)
{
   // Check if there is a node to remove
   if (pRemove == nullptr)
      return nullptr;

   // Save the nodes before and after the one being removed
   Node<T>* pPrev = pRemove->pPrev;
   Node<T>* pNext = pRemove->pNext;

   // Connect the previous node to the next node
   if (pPrev != nullptr)
      pPrev->pNext = pNext;

   // Connect the next node to the previous node
   if (pNext != nullptr)
      pNext->pPrev = pPrev;

   // Return the previous node, or the next node if there is no previous
   Node<T>* pReturn = (pPrev != nullptr) ? pPrev : pNext;

   // Delete the node from memory
   delete pRemove;

   return pReturn;
}


/**********************************************
 * INSERT 
 * Insert a new node the the value in "t" into a linked
 * list immediately before the current position.
 *   INPUT   : t - the value to be used for the new node
 *             pCurrent - a pointer to the node before which
 *                we will be inserting the new node
 *             after - whether we will be inserting after
 *   OUTPUT  : return the newly inserted item
 *   COST    : O(1)
 **********************************************/
template <class T>
inline Node<T>* insert(Node<T>* pCurrent,
   const T& t,
   bool after = false)
{
   // Create a new node with the given data
   Node<T>* pNew = new Node<T>(t);

   // If there is no current node, return the new node
   if (pCurrent == nullptr)
      return pNew;

   // Insert the new node after the current node
   if (after)
   {
      // Connect the new node to the surrounding nodes
      pNew->pPrev = pCurrent;
      pNew->pNext = pCurrent->pNext;

      // Update the next node's previous pointer if it exists
      if (pCurrent->pNext != nullptr)
         pCurrent->pNext->pPrev = pNew;

      // Connect the current node to the new node
      pCurrent->pNext = pNew;
   }
   else
   {
      // Insert the new node before the current node
      pNew->pNext = pCurrent;
      pNew->pPrev = pCurrent->pPrev;

      // Update the previous node's next pointer if it exists
      if (pCurrent->pPrev != nullptr)
         pCurrent->pPrev->pNext = pNew;

      // Connect the current node to the new node
      pCurrent->pPrev = pNew;
   }

   // Return the newly inserted node
   return pNew;
}


/******************************************************
 * SIZE
 * Find the size an unsorted linked list.  
 *  INPUT   : a pointer to the head of the linked list
 *            the value to be found
 *  OUTPUT  : number of nodes
 *  COST    : O(n)
 ********************************************************/
template <class T>
inline size_t size(const Node <T> * pHead)
{
   return 99;
}

/***********************************************
 * DISPLAY
 * Display all the items in the linked list from here on back
 *    INPUT  : the output stream
 *             pointer to the linked list
 *    OUTPUT : the data from the linked list on the screen
 *    COST   : O(n)
 **********************************************/
template <class T>
inline std::ostream & operator << (std::ostream & out, const Node <T> * pHead)
{
   return out;
}

/*****************************************************
 * CLEAR
 * Free all the data currently in the linked list
 *   INPUT   : pointer to the head of the linked list
 *   OUTPUT  : pHead set to NULL
 *   COST    : O(n)
 ****************************************************/
template <class T>
inline void clear(Node<T>*& pHead)
{
   // Keep deleting nodes until the list is empty
   while (pHead != nullptr)
   {
      // Save the current node so it can be deleted
      Node<T>* pDelete = pHead;

      // Move the head pointer to the next node
      pHead = pHead->pNext;

      // Delete the old node
      delete pDelete;
   }

   // Make sure the head pointer is null when finished
   pHead = nullptr;
}



