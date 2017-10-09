#include "user.hpp"
#include <fstream>
#include <zlib.h>

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

void User::saveUser(const char *filename)
{
    gzFile fp;
    int check = 0;
    int errnum = 6;
    fp =gzopen(filename, "wb");
    check = gzwrite(fp, this, sizeof(*this));
    if(check <= 0)
    {
        gzerror(fp, &errnum);
        std::cout << "Error writing to " << filename << " error (" << errnum << ")" << std::endl;
    }
    gzclose(fp);
}

void User::loadUser(const char *filename)
{
    gzFile fp;
    fp = gzopen(filename, "rb");
    gzread(fp, this, sizeof(*this));
    gzclose(fp);
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

