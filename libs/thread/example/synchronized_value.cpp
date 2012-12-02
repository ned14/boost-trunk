// (C) Copyright 2010 Just Software Solutions Ltd http://www.justsoftwaresolutions.co.uk
// (C) Copyright 2012 Vicente Botet
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//#define BOOST_THREAD_VERSION 4

// There is yet a limitation when BOOST_THREAD_PROVIDES_FUTURE_INVALID_AFTER_GET is defined
#define BOOST_THREAD_DONT_PROVIDE_FUTURE_INVALID_AFTER_GET

#include <iostream>
#include <string>
#include <boost/thread/synchronized_value.hpp>

#if ! defined BOOST_NO_CXX11_RVALUE_REFERENCES

void addTrailingSlashIfMissing(boost::synchronized_value<std::string> & path)
{
  boost::synchronized_value<std::string>::strict_synchronizer u=path.synchronize();

  if(u->empty() || (*u->rbegin()!='/'))
  {
    *u+='/';
  }
}

void f(const boost::synchronized_value<int> &v) {
  std::cout<<"v="<<*v<<std::endl;
}

void g(const boost::synchronized_value<int>::const_strict_synchronizer &v) {
  std::cout<<"v="<<*v<<std::endl;
}

bool checkIfMissingTrailingSlash(boost::synchronized_value<std::string> & path)
{
  boost::synchronized_value<std::string>::strict_synchronizer u=path.synchronize();

  return (u->empty() || (*u->rbegin()!='/'));
}

int main()
{
  {
    boost::synchronized_value<int> v1;
    *v1=42;
    std::cout<<"v1="<<*v1<<std::endl;
    f(v1);
    int i=*v1;
    std::cout<<"i="<<i<<std::endl;

    {
      boost::synchronized_value<int>::strict_synchronizer u=v1.synchronize();

      *u+=43;
      std::cout<<"v1="<<*u<<std::endl;
      g(u);
    }
    boost::synchronized_value<int> v2(2);
    std::cout<<"v2="<<*v2<<std::endl;
    v2 = 3;
    std::cout<<"v2="<<*v2<<std::endl;

    boost::synchronized_value<int> v3(v2);
    std::cout<<"v3="<<*v3<<std::endl;
    v3 = v1;
    std::cout<<"v3="<<*v3<<std::endl;

    std::cout<<"v2="<<*v3<<std::endl;
    std::cout<<"v3="<<*v3<<std::endl;
    swap(v3,v2);
    v1.swap(v2);
    std::cout<<"v3="<<*v3<<std::endl;
  }
  {
    boost::synchronized_value<std::string> s;
    addTrailingSlashIfMissing(s);
    std::cout<<"s="<<std::string(*s)<<std::endl;
  }
  {
    boost::synchronized_value<std::string> s;
    s->append("foo/");
    s.synchronize()->append("foo");
    addTrailingSlashIfMissing(s);
    std::cout<<"s="<<std::string(*s)<<std::endl;
  }
  return 0;
}

#else

int main()
{
  return 0;
}
#endif
