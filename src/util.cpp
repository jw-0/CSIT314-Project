#include "util.hpp"

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
