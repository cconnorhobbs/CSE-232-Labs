/***********************************************************************
 * Header:
 *    PRIORITY QUEUE
 * Summary:
 *    Our custom implementation of std::priority_queue
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *    This will contain the class definition of:
 *        priority_queue          : A class that represents a Priority Queue
 * Author
 *    Connor Hobbs and William Barr
 ************************************************************************/

#pragma once

#include <cassert>
#include "vector.h"
#include <utility>
#include <algorithm>

class TestPQueue;    // forward declaration for unit test class

namespace custom
{

   /*************************************************
    * P QUEUE
    * Create a priority queue.
    *************************************************/
   template<class T>
   class priority_queue
   {
      friend class ::TestPQueue; // give the unit test class access to the privates
      template <class TT>
      friend void swap(priority_queue<TT>& lhs, priority_queue<TT>& rhs);
   public:

      //
      // construct
      //
      priority_queue()
      {
      }

      priority_queue(const priority_queue& rhs)
      {
         container = rhs.container;
      }

      priority_queue(priority_queue&& rhs)
      {
         container = std::move(rhs.container);
      }

      template <class Iterator>
      priority_queue(Iterator first, Iterator last)
      {
         size_t count = 0;

         for (Iterator it = first; it != last; ++it)
            ++count;

         container.reserve(count);

         for (Iterator it = first; it != last; ++it)
            push(*it);
      }

      explicit priority_queue(custom::vector<T>&& rhs)
      {
      }

      explicit priority_queue(custom::vector<T>& rhs)
      {
      }

      ~priority_queue() {}

      //
      // Access
      //
      const T& top() const;

      //
      // Insert
      //
      void  push(const T& t);
      void  push(T&& t);

      //
      // Remove
      //
      void pop();

      //
      // Status
      //
      size_t size()  const
      {
         return container.size();
      }

      bool empty() const
      {
         return container.empty();
      }

   private:

      void heapify();                            // convert the container in to a heap
      bool percolateDown(size_t indexHeap);      // fix heap from index down. This is a heap index!

      custom::vector<T> container;

   };

   /************************************************
    * P QUEUE :: TOP
    * Get the maximum item from the heap: the top item.
    ***********************************************/
   template <class T>
   const T& priority_queue <T> ::top() const
   {
      if (container.empty())
         throw std::out_of_range("std:out_of_range");

      return container[0];
   }

   /**********************************************
    * P QUEUE :: POP
    * Delete the top item from the heap.
    **********************************************/
   template <class T>
   void priority_queue <T> ::pop()
   {
      if (container.empty())
         return;

      if (container.size() == 1)
      {
         container.pop_back();
         return;
      }

      // Move the last element to the root
      container[0] = std::move(container.back());
      container.pop_back();

      // Percolate down to restore the max-heap
      size_t i = 0;

      while (true)
      {
         size_t largest = i;
         size_t left = 2 * i + 1;
         size_t right = 2 * i + 2;

         // Check the left child
         if (left < container.size() &&
            container[left] > container[largest])
         {
            largest = left;
         }

         // Check the right child
         if (right < container.size() &&
            container[right] > container[largest])
         {
            largest = right;
         }

         // Swap with the larger child if necessary
         if (largest != i)
         {
            std::swap(container[i], container[largest]);
            i = largest;
         }
         else
         {
            break;
         }
      }
   }

   /*****************************************
    * P QUEUE :: PUSH
    * Add a new element to the heap, reallocating as necessary
    ****************************************/
   template <class T>
   void priority_queue <T> ::push(const T& t)
   {
      container.push_back(t);

      size_t i = container.size() - 1;

      while (i > 0)
      {
         size_t parent = (i - 1) / 2;

         if (container[i] > container[parent])
         {
            std::swap(container[i], container[parent]);
            i = parent;
         }
         else
         {
            break;
         }
      }
   }

   template <class T>
   void priority_queue <T> ::push(T&& t)
   {
      container.push_back(std::move(t));

      size_t i = container.size() - 1;

      while (i > 0)
      {
         size_t parent = (i - 1) / 2;

         if (container[i] > container[parent])
         {
            std::swap(container[i], container[parent]);
            i = parent;
         }
         else
         {
            break;
         }
      }
   }

   /************************************************
    * P QUEUE :: PERCOLATE DOWN
    * The item at the passed index may be out of heap
    * order. Take care of that little detail!
    * Return TRUE if anything changed.
    ************************************************/
   template <class T>
   bool priority_queue <T> ::percolateDown(size_t indexHeap)
   {
      return false;
   }

   /************************************************
    * P QUEUE :: HEAPIFY
    * Turn the container into a heap.
    ************************************************/
   template <class T>
   void priority_queue <T> ::heapify()
   {
   }

   /************************************************
    * SWAP
    * Swap the contents of two priority queues
    ************************************************/
   template <class T>
   inline void swap(custom::priority_queue <T>& lhs,
      custom::priority_queue <T>& rhs)
   {
   }

};

