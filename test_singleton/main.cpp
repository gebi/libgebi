#include <gebi/singleton.hpp>
using namespace Gebi;

#include <iostream>
#include <string>
using namespace std;

class Test
{
  private:
    string msg_;

  public:
    Test()
      { msg_="Class Test"; cout << "Constructor Test" << endl; }
    ~Test()
      { cout << "Destructor Test" << endl; }
    void setMsg(string const &msg)
      { msg_ = msg; }
    void printMsg()
      { cout << msg_ << endl; }
};

typedef Singleton<Test> SingletonTest;

int main()
{
  Test *a = &SingletonTest::instance();
  a->printMsg();

  Test *b = &SingletonTest::instance();
  b->printMsg();

  Test c = Singleton<Test, createGamma>::instance();
  
  a->setMsg("TEEEEEEEEEEST written into a");
  cout << "Message printed from b: ";
  b->printMsg();
  c.printMsg();
}
