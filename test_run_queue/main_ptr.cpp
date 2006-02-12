#include "run_queue.hpp"
using namespace gebi;

#include <iostream>
#include <memory>
using std::auto_ptr;
using namespace std;

class Test
{
  private:
    int i_;

  public:
    Test(const int init) : i_(init) { cerr << "Constructor: " << i_ << endl; }
    Test(const Test &src) : i_(src.i_) { cerr << "Copyconstructor: " << i_ << endl; }
    Test operator=(const Test &src) { cerr << "Assignment from " << src.i_ << "to " << i_ << endl; return *this; }
    ~Test() {cerr << "Destructor: " << i_ << endl; }

    int getValue() const { return i_; }
};

typedef ZCRunQueue<Test*, 5> Myrq;

void getTest(int i, Myrq &src)
{
  if(src.empty()) {
    cerr << i << " = NULL" << endl;
  } else {
    cerr << i << " = " << src.top()->getValue() << endl;
    src.pop();
  }
}
    
int main()
{
  Myrq test;
  cerr << "number of elements = " << test.size() << endl;

  Test zero(0);
  Test one(1);
  Test two(2);
  test.pushAt(0, &zero);
  test.pushAt(1, &one);
  test.pushAt(2, &two);

  getTest(1, test);
  getTest(2, test);
  test.pushAt(1, &one);

  test.dumpArray();

  cerr << "number of elements = " << test.size() << endl;
  return 0;
}

