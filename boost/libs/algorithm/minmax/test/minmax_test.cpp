#include <utility>
#include <functional>
#include <iostream>

#include <boost/algorithm/minmax.hpp>
#include <boost/test/included/test_exec_monitor.hpp>

class custom {
  int m_x;
  friend std::ostream& operator<<(std::ostream& str, custom const& x);
public:
  explicit custom(int x = 0) : m_x(x) {}
  custom(custom const& y) : m_x(y.m_x) {}
  bool operator==(custom const& y) const { return m_x == y.m_x; }
  bool operator<(custom const& y) const { return m_x < y.m_x; }
  custom operator+(custom const& y) const { return custom(m_x+y.m_x); }
  custom& operator+=(custom const& y) { m_x += y.m_x; return *this; }
};

std::ostream&
operator<<(std::ostream& str, custom const& x)
{
  return  str << x.m_x;
}

template <class Value>
struct less_count : std::less<Value> {
  typedef std::less<Value> Base;
  less_count(less_count<Value> const& lc) : m_counter(lc.m_counter) {}
  less_count(int& counter) : m_counter(counter) {}
  bool operator()(Value const& a, Value const& b) const {
    ++m_counter;
    return Base::operator()(a,b);
  }
  void reset() {
    m_counter = 0;
  }
private:
  int& m_counter;
};

template <class Value>
void test(char*)
{
  using namespace boost;
  Value zero(0), one(1);
  int counter = 0;
  less_count<Value> lc(counter);

  // Test functionality
  tuple<Value const&, Value const&> result1 = minmax(zero, one);
  BOOST_CHECK_EQUAL( result1.get<0>(), zero );
  BOOST_CHECK_EQUAL( result1.get<1>(), one );

  tuple<Value const&, Value const&> result2 = minmax(one, zero);
  BOOST_CHECK_EQUAL( result2.get<0>(), zero );
  BOOST_CHECK_EQUAL( result2.get<1>(), one );
  
  // Test functionality and number of comparisons
  lc.reset();
  tuple<Value const&, Value const&> result3 = minmax(zero, one, lc );
  BOOST_CHECK_EQUAL( result3.get<0>(), zero );
  BOOST_CHECK_EQUAL( result3.get<1>(), one );
  BOOST_CHECK_EQUAL( counter, 1 );

  lc.reset();
  tuple<Value const&, Value const&> result4 = minmax(one, zero, lc );
  BOOST_CHECK_EQUAL( result4.get<0>(), zero );
  BOOST_CHECK_EQUAL( result4.get<1>(), one );
  BOOST_CHECK_EQUAL( counter, 1);
}

int test_main( int , char* [] )
{
  test<int>("builtin");
  test<custom>("custom ");

  return 0;
}
