#ifndef run_queue_hpp___
#define run_queue_hpp___

#ifdef TEST_COMPILE
#include "threads.hpp"
#else
#include <gebi/threads.hpp>
#endif

#include <iostream>
using std::cout;
using std::endl;

#include <list>
using std::list;

#include <stdexcept>
using std::runtime_error;

namespace Gebi
{

  /* NOTE
   * These RunQueues are optimized for a small number of different priorities and _MANY_ elements
   *
   * The number of different priorities has to be given at compiletime!
   * There is NO chance to change this at runtime.
   *
   * from a 5h discussion on ##c++ on freenode:
   * the algorithm (template) is O(1) in regards to the number of elements in
   * the container, and O(n) in regards to the number of different priorities,
   * but the implementation is always O(1)
   */


  /*
   * RunQueueBase
   * gives the base functions to both RunQueue and ZCRunQueue (but NOT to ZCRunQueue<T*, ...>)
   *
   */
  // template<class T, unsigned Priorities, class RWLockType = NullMutex>
  // class RunQueueBase
  // class RunQueueBase  {{{
  template<class T, unsigned Priorities, class RWLockType = NullMutex>
  class RunQueueBase
  {
    protected:
      mutable RWLockType lock_;
      unsigned lowest_prio_;
      unsigned num_elements_;
      list<T> array_[Priorities + 1];

      typedef Guard<RWLockType, LockRead> GuardR;
      typedef Guard<RWLockType, LockWrite> GuardW;

      // needs a write lock
      inline void _pop()
      {
        array_[lowest_prio_].pop_front();

        // no more elements, return
        --num_elements_;
        if(num_elements_ == 0) {
          lowest_prio_ = Priorities;
          return;
        }

        // find the next element
        unsigned i;
        for(i = lowest_prio_; i <= Priorities; i++) {
          if(!array_[i].empty())
            break;
        }
        lowest_prio_ = i;
      }

    public:
      RunQueueBase() : lowest_prio_(Priorities + 1), num_elements_(0) {}
      virtual ~RunQueueBase() {}

      unsigned size() const
      {
        //GuardR guard(lock_);
        return num_elements_;
      }

      bool empty() const
      {
        //GuardR guard(lock_);
        return (num_elements_ == 0);
      }

      /* NOTE
       * top() and pop() are very problematic to use in multithreaded environments
       * you _have_to_ lock it extern, because another thread is able to delete
       * the element befor you are able to delete you top'ed element.
       * or only one thread removes elements from the queue.
       */

      void pop()
      {
        //GuardW guard(lock_);
        if(num_elements_ == 0)
          throw runtime_error("No more elements in the queue");
        GuardW guard(lock_);
        _pop();
      }
       
      void dumpArray() const
      {
        unsigned i;
        for(i = 0; i < Priorities; i++) {
          cout << i << ": ";
          typename list<T>::size_type num = this->array_[i].size();
          if(num)
            cout << num << " Task(s)" << endl;
          else
            cout << "Nothing" << endl;
        }
      }
  }; // }}}


  /* NOTE
   * top() and pop() are very problematic to use in multithreaded environments
   * you _have_to_ lock it extern, because another thread is able to delete
   * the element befor you are able to delete you top'ed element.
   * or only one thread removes elements from the queue.
   */


  /*
   * RunQueue
   * should be used for normal Objects, this Queue has copy semantics on input
   *
   */
  // template<class T, unsigned Priorities, class RWLockType = NullMutex>
  // class RunQueue : public RunQueueBase<T, Priorities, RWLockType>
  // class RunQueue  {{{
  template<class T, unsigned Priorities, class RWLockType = NullMutex>
  class RunQueue : public RunQueueBase<T, Priorities, RWLockType>
  {
    protected:
      typedef Guard<RWLockType, LockRead> GuardR;
      typedef Guard<RWLockType, LockWrite> GuardW;

    public:
      RunQueue() {}
      virtual ~RunQueue() {}

      void pushAt(const unsigned prio, T const &src)
      {
        if(prio > Priorities)
          return;
        GuardW guard(this->lock_);
        this->array_[prio].push_back(src);
        this->num_elements_++;
        if(prio < this->lowest_prio_)
          this->lowest_prio_ = prio;
      }

      T &get()
      {
        //GuardW guard(lock_);
        if(this->num_elements_ == 0)
          throw runtime_error("No more elements in the queue");
        GuardW guard(this->lock_);
        T &ref = this->array_[this->lowest_prio_].front();
        this->_pop();
        return ref;
      }

      template<typename AutoPtrType>
      AutoPtrType getAPtr()
      {
        //GuardW guard(lock_);
        if(this->num_elements_ == 0)
          throw runtime_error("No more elements in the queue");
        GuardW guard(this->lock_);
        AutoPtrType instance(this->array_[this->lowest_prio_].front());
        this->_pop();
        return instance;
      }

      const T &top() const
      {
        //GuardR guard(lock_);
        if(this->num_elements_ == 0)
          throw runtime_error("No more elements in the queue");
        GuardR guard(this->lock_);
        return this->array_[this->lowest_prio_].front();
      }
  }; // }}}


  /*
   * ZCRunQueue
   * this RunQueue does not copy on insertion and SHOULD NOT BE USED with normal Objects
   * but only with Pointers
   *
   * also, this class uses template specialisation so that for all Pointer-types only one
   * template is instantiated (void*) + a wrapper for the concrete type.
   *
   */
  // template<class T, unsigned Priorities, class RWLockType = NullMutex>
  // class ZCRunQueue : public RunQueueBase<T, Priorities, RWLockType>
  // SHOULD NOT BE USED  {{{
  template<class T, unsigned Priorities, class RWLockType = NullMutex>
  class ZCRunQueue : public RunQueueBase<T, Priorities, RWLockType>
  {
    protected:
      typedef Guard<RWLockType, LockRead> GuardR;
      typedef Guard<RWLockType, LockWrite> GuardW;

    public:
      ZCRunQueue() {}
      virtual ~ZCRunQueue() {}

      void pushAt(const unsigned prio, T src)
      {
        if(prio > Priorities)
          return;
        GuardW guard(this->lock_);
        this->array_[prio].push_back(src);
        this->num_elements_++;
        if(prio < this->lowest_prio_)
          this->lowest_prio_ = prio;
      }

      bool get(T* bp)
      {
        //GuardW guard(lock_);
        if(this->num_elements_ == 0)
          return false;
        GuardW guard(this->lock_);
        *bp = this->array_[this->lowest_prio_].front();
        this->_pop();
        return true;
      }

      template<class AutoPointerType>
      AutoPointerType getAPtr()
      {
        //GuardW guard(lock_);
        if(this->num_elements_ == 0)
          throw runtime_error("No more elements in the queue");
        GuardW guard(this->lock_);
        AutoPointerType instance(this->array_[this->lowest_prio_].front());
        this->_pop();
        return instance;
      }

      T top() const
      {
        //GuardR guard(lock_);
        if(this->num_elements_ == 0)
          throw runtime_error("No more elements in the queue");
        GuardR guard(this->lock_);
        return this->array_[this->lowest_prio_].front();
      }
  }; // }}}

  // concrete implementation for void*  {{{
  template<unsigned Priorities, class RWLockType>
  class ZCRunQueue<void*, Priorities, RWLockType> : public RunQueueBase<void*, Priorities, RWLockType>
  {
    protected:
      typedef Guard<RWLockType, LockRead> GuardR;
      typedef Guard<RWLockType, LockWrite> GuardW;

    public:
      ZCRunQueue() {}
      virtual ~ZCRunQueue() {}

      void pushAt(const unsigned prio, void* src)
      {
        if(prio > Priorities)
          return;
        GuardW guard(this->lock_);
        this->array_[prio].push_back(src);
        this->num_elements_++;
        if(prio < this->lowest_prio_)
          this->lowest_prio_ = prio;
      }

      void* get()
      {
        if(this->num_elements_ == 0)
          throw runtime_error("No more elements in the queue");
        GuardW guard(this->lock_);
        void *tmp = this->array_[this->lowest_prio_].front();
        this->_pop();
        return tmp;
      }

      bool get(void** bp)
      {
        //GuardW guard(lock_);
        if(this->num_elements_ == 0)
          return false;
        GuardW guard(this->lock_);
        *bp = this->array_[this->lowest_prio_].front();
        this->_pop();
        return true;
      }

      template<class AutoPointerType>
      AutoPointerType getAPtr()
      {
        //GuardW guard(lock_);
        if(this->num_elements_ == 0)
          throw runtime_error("No more elements in the queue");
        GuardW guard(this->lock_);
        AutoPointerType instance(this->array_[this->lowest_prio_].front());
        this->_pop();
        return instance;
      }

      void* top() const
      {
        //GuardR guard(lock_);
        if(this->num_elements_ == 0)
          throw runtime_error("No more elements in the queue");
        GuardR guard(this->lock_);
        return this->array_[this->lowest_prio_].front();
      }
  }; // }}}

  // wrapper, ONLY for casting  {{{
  template<class T, unsigned Priorities, class RWLockType>
  class ZCRunQueue<T*, Priorities, RWLockType> : ZCRunQueue<void*, Priorities, RWLockType>
  {
    protected:
      typedef ZCRunQueue<void*, Priorities, RWLockType> WrappedQueue;
      typedef T* Type;

    public:
      ZCRunQueue() {}
      virtual ~ZCRunQueue() {}

      void pushAt(const unsigned prio, Type src)
      {
        WrappedQueue::pushAt(prio, reinterpret_cast<void*>(src));
      }

      bool get(Type* bp)
      {
        return WrappedQueue::get(reinterpret_cast<void**>(bp));
      }

      // hmmm... useless?
      template<class AutoPointerType>
      AutoPointerType getAPtr()
      {
        AutoPointerType instance(reinterpret_cast<Type>(WrappedQueue::get()));
        return instance;
      }

      Type top() const
      {
        return reinterpret_cast<Type>(WrappedQueue::top());
      }

      unsigned size() const
      {
        return WrappedQueue::size();
      }

      bool empty() const
      {
        return WrappedQueue::empty();
      }

      void pop()
      {
        WrappedQueue::pop();
      }
       
      void dumpArray() const
      {
        WrappedQueue::dumpArray();
      }
  }; // }}}
  
} // end namespace Gabi

// vim:foldmethod=marker
#endif
