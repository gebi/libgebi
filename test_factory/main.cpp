#include "factory.hpp"
using namespace Gebi;

#include <iostream>
#include <stdexcept>
using namespace std;

// testclasses {{{
class Base
{
  public:
    Base() { cout << "Constructor: Base" << endl; }
    virtual ~Base() { cout << "Destructor: Base" << endl; }
    virtual void print() { cout << "Base Class HALLO" << endl; }
    virtual void setMsg(string const &msg) {}
};

class DerivedA : public Base
{
  protected:
    string msg_;
  public:
    DerivedA()  { msg_="DerivedA Class HALLO"; cout << "Constructor: DerivedA" << endl; }
    virtual ~DerivedA()  { cout << "Destructor: DerivedA" << endl; }
    virtual void print()  { cout << msg_ << endl; }
    void setMsg(string const &msg)  { msg_ = msg; }
};

class DerivedB : public Base
{
  public:
    DerivedB() { cout << "Constructor: DerivedB" << endl; }
    virtual ~DerivedB() { cout << "Destructor: DerivedB" << endl; }
    virtual void print() { cout << "DerivedB Class HALLO" << endl; }
};
// }}}

template<class T>
auto_ptr<T> create()
  { return auto_ptr<T>(new T()); }

template<class T>
auto_ptr<T> create(T init)
  { return auto_ptr<T>(new T(init)); }


typedef Factory<Base, std::auto_ptr<Base>, NullMutex> MyFactory;

int main()
{
  try
  {
    auto_ptr<int> test = create<int>(10);
    auto_ptr<double> test1 = create<double>(10.05);
    auto_ptr<float> test2(new float(30.3));
    cout << *test << endl;
    cout << *test1 << endl;
    cout << *test2 << endl;

    MyFactory factory;
    factory.add<Base>("Base");
    factory.add<DerivedA>("DerivedA");
    factory.add<DerivedB>("DerivedB");

    MyFactory::AutoPtr base = factory.get("Base");
    MyFactory::AutoPtr da = factory.get("DerivedA");
    base->print();
    da->print();

    cout << "\ntest:\n";
    MyFactory::AutoPtr da1 = factory.get("DerivedA");
    da1->setMsg("Another DerivedA Class HALLO");
    da->print();
    da1->print();
    cout << "test: ENDE\n" << endl;
    
    base.reset();
    factory.del("DerivedB");
    
    MyFactory factory1;
    factory1.add<Base>("Base");
    try {
      MyFactory::AutoPtr fac1db = factory1.get("DerivedB1");
    } catch(exception &ex) {
      cout << "Exeption1: Module " << ex.what() << " not available" << endl;
    }

    try {
      MyFactory::AutoPtr db = factory.get("DerivedB1");
    } catch(exception &ex) {
      cout << "Exeption2: Module " << ex.what() << " not available" << endl;
    }

    MyFactory::AutoPtr db = factory.get("DerivedB2");
  }
  catch(exception &ex) {
    cout << "Exeption3: Module " << ex.what() << " not available" << endl;
  }
  catch(...) {
    cout << "Unknown exception cought" << endl;
  }

  return 0;
}

// vim:foldmethod=marker
