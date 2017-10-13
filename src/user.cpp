#include "user.hpp"
#include <fstream>
#include <cgicc/HTMLClasses.h>
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

User::User()
{
    //userCount = 0;
    id = 0;
    rating = 0.0;
}

void User::createUser(cgicc::Cgicc formdata)
{
    username = getValue("username", formdata);
    firstName = getValue("firstName", formdata);
    lastName = getValue("lastName", formdata);
    email = getValue("email", formdata);
    phone = getValue("phone", formdata);
    password = getValue("password", formdata);
    ID += 1;
    id = ID;
    std::cout << cgicc::body() << "<script> alert(\"User created succesfully!\"); window.history.back();  </script>" << std::endl;
    //userCount++;
}

void User::saveUser(const char *fileName)
{
    std::ofstream out;
    out.open(fileName, std::ofstream::out | std::ofstream::app);
    if(out.is_open())
    {
        out << id << "\t" << username << "\t" << firstName << "\t" << lastName << "\t" << email << "\t" << phone << "\t" << password << std::endl;
        std::cout << "<script> alert(\" Successfully wrote user! \"); </script>" << std::endl;
    }
    else
        std::cout << "<script> alert(\"Cannot open " << fileName << "!\")</script>" << std::endl;
    out.close();
}

std::istream &User::loadUser(std::istream &in)
{
    in >> id >> username >> firstName >> lastName >> email >> phone >> password;
    return in;
}

std::ostream &User::displayUser(std::ostream &out)
{
    out << id << "\t" << username << "\t" << firstName << "\t" << lastName << "\t" << email << "\t" << phone << "\t" << password << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, User &user)
{
    in >> user.id >> user.username >> user.firstName >> user.lastName >> user.email >> user.phone >> user.password;
    return in;
}

void loadUsers(std::vector<User> &users, const char *fileName)
{
    std::ifstream in;
    User user;
    in.open(fileName);
    int i = 0;
    if(in.is_open())
    {
        while(!in.eof())
        {
            in >> user;
            users.push_back(user);
            ID = user.getID();
            i++;
            if(i > 101)
                break;
        }
        std::cout << "<script> alert(\"Successfully loaded users.dat!\") </script>" << std::endl;
    }
    else
        std::cout << "<script> alert(\"Cannot open " << fileName << "!. Cannot load users into system.\")</script>" << std::endl;
    in.close();
}