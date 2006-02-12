#ifndef threads_hpp___
#define threads_hpp___

#include <pthread.h>

namespace Gebi
{

  /* NOTE:
   * currently only a ThreadMutex is available for Windows (RWMutex is
   * actually the same as ThreadMutex).
   * you have to solve the headerfile and RWMutex issue on windows on your own.
   */

  // ThreadMutex  {{{
#ifdef _WINDOWS_
  class ThreadMutex
  { 
    private:
      CRITICAL_SECTION lock_;

      ThreadMutex(const ThreadMutex &src);
      ThreadMutex &operator=(const ThreadMutex &src);

    public:
      ThreadMutex()  { InitialiseCriticalSection(&lock_); }
      ~ThreadMutex() { DeleteCriticalSection(&lock_); }

      int aquire()  { EnterCriticalSection(&lock_); return 0; }
      int release() { LeaveCriticalSection(&lock_); return 0; }
      
      int aquireRead()  { EnterCriticalSection(&lock_); return 0; }
      int releaseRead() { LeaveCriticalSection(&lock_); return 0; }

      int aquireWrite()  { EnterCriticalSection(&lock_); return 0; }
      int releaseWrite() { LeaveCriticalSection(&lock_); return 0; }
  };
#else
  class ThreadMutex
  { 
    private:
      pthread_mutex_t lock_;

      ThreadMutex(const ThreadMutex &src);
      ThreadMutex &operator=(const ThreadMutex &src);

    public:
      ThreadMutex()  { pthread_mutex_init(&lock_, 0); }
      ~ThreadMutex() { pthread_mutex_destroy(&lock_); }

      int aquire()  { return pthread_mutex_lock(&lock_); }
      int release() { return pthread_mutex_unlock(&lock_); }

      int aquireRead()  { return pthread_mutex_lock(&lock_); }
      int releaseRead() { return pthread_mutex_unlock(&lock_); }
      
      int aquireWrite()  { return pthread_mutex_lock(&lock_); }
      int releaseWrite() { return pthread_mutex_unlock(&lock_); }
  };
#endif
  // }}}

  // NullMutex  {{{
  class NullMutex
  { 
    private:
      NullMutex(const NullMutex &src);
      NullMutex &operator=(const NullMutex &src);

    public:
      NullMutex()  {}
      ~NullMutex() {}

      int aquire()  { return 0; }
      int release() { return 0; }

      int aquireRead()  { return 0; }
      int releaseRead() { return 0; }

      int aquireWrite()  { return 0; }
      int releaseWrite() { return 0; }
  }; // }}}

  // RWMutex  {{{
#ifdef _WINDOWS_
  class RWMutex
  { 
    private:
      CRITICAL_SECTION lock_;

      RWMutex(const RWMutex &src);
      RWMutex &operator=(const RWMutex &src);

    public:
      RWMutex()  { InitialiseCriticalSection(&lock_); }
      ~RWMutex() { DeleteCriticalSection(&lock_); }

      int aquireRead()  { EnterCriticalSection(&lock_); return 0; }
      int releaseRead() { LeaveCriticalSection(&lock_); return 0; }
      
      int aquireWrite()  { EnterCriticalSection(&lock_); return 0; }
      int releaseWrite() { LeaveCriticalSection(&lock_); return 0; }
  };
#else
  class RWMutex
  {
    private:
      pthread_rwlock_t lock_;

      RWMutex(const RWMutex &src);
      RWMutex &operator=(const RWMutex &src);

    public:
      RWMutex()  { pthread_rwlock_init(&lock_, 0); }
      ~RWMutex() { pthread_rwlock_destroy(&lock_); }

      int aquireRead()  { return pthread_rwlock_rdlock(&lock_); }
      int releaseRead() { return pthread_rwlock_unlock(&lock_); }

      int aquireWrite()  { return pthread_rwlock_wrlock(&lock_); }
      int releaseWrite() { return pthread_rwlock_unlock(&lock_); }
  };
#endif
  // }}}

  /* NOTE:
   * ThreadMutex / NullMutex => LockMutex
   * RWMutex / NullMutex => LockRead, LockWrite
   */

  // LockBridges: LockRead, LockWrite, LockMutex  {{{
  template<typename Lock>
  class LockRead
  {
    protected:
      int aquireLock(Lock &lock)  { return lock.aquireRead(); }
      int releaseLock(Lock &lock) { return lock.releaseRead(); }
  };

  template<typename Lock>
  class LockWrite
  {
    protected:
      int aquireLock(Lock &lock)  { return lock.aquireWrite(); }
      int releaseLock(Lock &lock) { return lock.releaseWrite(); }
  };

  template<typename Lock>
  class LockMutex
  {
    protected:
      int aquireLock(Lock &lock)  { return lock.aquire(); }
      int releaseLock(Lock &lock) { return lock.release(); }
  }; // }}}

  // class Guard  {{{
  template<typename Lock, template<typename> class LockBridge = LockMutex >
  class Guard : public LockBridge<Lock>
  { 
    private:
      Lock &lock_;
      int result_;

      Guard(Guard<Lock, LockBridge> &src) {}
      Guard &operator=(const Guard &src) {}

    public:
      Guard(Lock &lock) : lock_(lock)
        { result_ = aquireLock(lock_); }

      ~Guard()
      {
        if(result_ != -1)
          releaseLock(lock_);
      }

      void aquire() { result_ = aquireLock(lock_); }
      void release()
      {
        if(result_ != -1)
          releaseLock(lock_);
      }
  };
  // }}}

} // end namespace Gebi

// vim:foldmethod=marker
#endif
