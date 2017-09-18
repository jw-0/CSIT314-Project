#include "user.hpp"
#include <fstream>

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

void User::createUser(cgicc::Cgicc formdata)
{
    username = getValue("username", formdata);
    firstName = getValue("firstName", formdata);
    lastName = getValue("lastName", formdata);
    service = getValue("service", formdata);
    offerDate = getValue("offerDate", formdata);
    endDate = getValue("endDate", formdata);
    email = getValue("email", formdata);
    location = getValue("location", formdata);
}

// A simple wrapper around displayUser so we don't get confused by the names
std::ostream &User::saveUser(std::ostream &out)
{
    displayUser(out);
    return out;
}

std::istream &User::loadUser(std::istream &in)
{
    in >> username >> firstName >> lastName >> service >> offerDate >> endDate
       >> email >> location;
    return in;
}

std::ostream &User::displayUser(std::ostream &out)
{
    out << username << std::endl;
    out << firstName << std::endl;
    out << lastName << std::endl;
    out << service << std::endl;
    out << offerDate << std::endl;
    out << endDate << std::endl;
    out << email << std::endl;
    out << location << std::endl;
    return out;
}

