#include "util.hpp"
#include <iostream> 

void alert(std::string msg)
{
    std::cout << "<script> alert(\"" + msg + "\"); </script>" << std::endl; 
}

std::string getValue(const char *valueName, cgicc::Cgicc formdata)
{
    auto iter = formdata.getElement(valueName);
    std::string retval;
    if(!iter->isEmpty() && iter != (*formdata).end())
        retval = **iter;
    else
        retval = "null";

    return retval;
}
