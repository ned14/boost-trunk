
    
#include <boost/function.hpp>
#include <iostream>
#include <functional>


struct X {
  int foo(int);
};

int main()
{
    
  boost::function1<int, int> f;
  X x;
  f = std::bind1st(std::mem_fun(&X::foo), &x);

  f(5); // Call x.foo(5)

}
    