#ifndef factory_h___
#define factory_h___

#include <threads.hpp>

#include <map>
#include <memory>
#include <utility>
#include <stdexcept>

namespace gebi
{
  namespace FactoryPrivate
  {
    template<typename BaseClass,
             typename RealClass>
    BaseClass *createInstance()
    {
      return new RealClass();
    }
  }

  template<typename BaseClass,
           typename BaseAutoPtr = std::auto_ptr<BaseClass>,
           typename LockType = NullMutex,
           typename Creator = BaseClass*(*)(),
           typename Identifier = std::string>
           // ATTENTION: only change the Identifier if you EXACTLY know what you are doing,
           // Identifier should implement methode c_str()
  class Factory
  {
    private:
      Factory(Factory const &src);
      Factory &operator=(const Factory &src);
      LockType lock_;

    protected:
      typedef std::map<Identifier, Creator> CallbackMap;
      typedef typename CallbackMap::const_iterator CallbackMapConstIterator;
      CallbackMap callbacks_;

    public:
      typedef BaseAutoPtr AutoPtr;
      typedef Guard<LockType, LockRead> GuardR;
      typedef Guard<LockType, LockWrite> GuardW;

      Factory() {}
      ~Factory() {}

      template<class RealClass>
      bool add(Identifier const &ident)
      {
        GuardW guard(lock_);
        return callbacks_.insert(std::make_pair(ident, FactoryPrivate::createInstance<BaseClass, RealClass>)).second;
      }

      bool add(Identifier const &ident, Creator const &creator)
      {
        GuardW guard(lock_);
        return callbacks_.insert(make_pair(ident, creator)).second;
      }

      bool supports(Identifier const &ident)
      {
        GuardR guard(lock_);
        return (callbacks_.find(ident) != callbacks_.end());
      }

      void del(Identifier const &ident)
      {
        GuardW guard(lock_);
        callbacks_.erase(ident);
      }

      BaseAutoPtr get(Identifier const &ident)
      {
        GuardR guard(lock_);
        CallbackMapConstIterator iter = callbacks_.find(ident);
        if(iter != callbacks_.end())
        {
          BaseAutoPtr instance((iter->second)());
          return instance;
        }
        else
          throw std::runtime_error(ident.c_str());
      }
  };
} // end namespace gebi

#endif
// vim:foldmethod=marker
