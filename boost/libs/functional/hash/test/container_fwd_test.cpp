#include <boost/functional/detail/container_fwd.hpp>

template <class charT, class traits, class Allocator>
void test(std::basic_string<charT, traits, Allocator> const&)
{
}
    
template <class T, class Allocator>
void test(std::deque<T, Allocator> const&)
{
}

template <class T, class Allocator>
void test(std::list<T, Allocator> const&)
{
}

template <class T, class Allocator>
void test(std::vector<T, Allocator> const&)
{
}

template <class Key, class T, class Compare, class Allocator>
void test(std::map<Key, T, Compare, Allocator> const&)
{
}

template <class Key, class T, class Compare, class Allocator>
void test(std::multimap<Key, T, Compare, Allocator> const&)
{
}

template <class Key, class Compare, class Allocator>
void test(std::set<Key, Compare, Allocator> const&)
{
}

template <class Key, class Compare, class Allocator>
void test(std::multiset<Key, Compare, Allocator> const&)
{
}

template <std::size_t N>
void test(std::bitset<N> const&)
{
}

template <class T>
void test(std::complex<T> const&)
{
}

#include <deque>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <string>
#include <complex>

int main()
{
    std::deque<int> x1;
    std::list<std::string> x2;
    std::vector<float> x3;
    std::vector<bool> x4;
    std::map<int, int> x5;
    std::multimap<float, int*> x6;
    std::set<std::string> x7;
    std::multiset<std::vector<int> > x8;
    std::bitset<10> x9;
    std::string x10;
    std::complex<double> x11;

    test(x1);
    test(x2);
    test(x3);
    test(x4);
    test(x5);
    test(x6);
    test(x7);
    test(x8);
    test(x9);
    test(x10);
    test(x11);
}
