#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <vector>

using namespace boost::python;

class Abstract
{
public:   
    virtual std::string    f() =0;
};

class Concrete1 : public Abstract
{
public:   
    virtual std::string    f()    { return "harru"; }
};

typedef std::vector<Abstract*>   ListOfObjects;

class DoesSomething
{
public:
    DoesSomething()    {}
   
    ListOfObjects   returnList()    
    {
        ListOfObjects lst; 
        lst.push_back(new Concrete1()); return lst; 
    }
};

BOOST_PYTHON_MODULE(pointer_vector_ext)
{       
class_<Abstract, boost::noncopyable>("Abstract", no_init)
    .def("f", &Abstract::f)
    ;

class_<ListOfObjects>("ListOfObjects")
   .def( vector_indexing_suite<ListOfObjects>() )  
    ;

class_<DoesSomething>("DoesSomething")
    .def("returnList", &DoesSomething::returnList)
    ;
}


