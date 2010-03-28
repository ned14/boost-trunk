#include <boost/range/adaptor/copied.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
    using namespace boost::assign;
    using namespace boost::adaptors;
    
    std::vector<int> input;
    input += 1,2,3,4,5,6,7,8,9,10;
    
    boost::copy(
        input | copied(1, 5),
        std::ostream_iterator<int>(std::cout, ","));
        
    return 0;
}

