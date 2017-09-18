#include "user.hpp"

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

void User::saveUser()
{
}

void User::displayUser()
{
    std::cout << username << std::endl;
    std::cout << firstName << std::endl;
    std::cout << lastName << std::endl;
    std::cout << service << std::endl;
    std::cout << offerDate << std::endl;
    std::cout << endDate << std::endl;
    std::cout << email << std::endl;
    std::cout << location << std::endl;
}

