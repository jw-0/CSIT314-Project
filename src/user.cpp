#include "user.hpp"
#include <fstream>
#include <cgicc/HTMLClasses.h>
#include "util.hpp"


User::User()
{
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
}

void User::saveUser(const char *fileName)
{
    std::ofstream out;
    out.open(fileName, std::ofstream::app);
    if(out.is_open())
    {
        out << *this;
        //std::cout << "<script> alert(\" Successfully wrote user! \"); </script>" << std::endl;
    }
    else
        std::cout << "<script> alert(\"Cannot open " << fileName << "!\")</script>" << std::endl;
    out.close();
}

bool operator==(const User &lhs, const User &rhs)
{
    if(lhs.id == rhs.id && 
       lhs.username == rhs.username &&
       lhs.firstName == rhs.firstName &&
       lhs.lastName == rhs.lastName &&
       lhs.email == rhs.email &&
       lhs.phone == rhs.phone &&
       lhs.password == rhs.password)
        return true;
    return false;
}

std::istream &operator>>(std::istream &in, User &user)
{
    in >> user.id >> user.username >> user.firstName >> user.lastName >> user.email >> user.phone >> user.password;
    return in;
}

std::ostream &operator<<(std::ostream &out, const User &user)
{
    out << user.id << "\t" << user.username << "\t" <<  user.firstName << "\t" << user.lastName << "\t" << user.email << "\t" << user.phone << "\t" << user.password << std::endl;;
    return out;
}


void loadUsers(std::vector<User> &users, const char *fileName)
{
    std::ifstream in;
    User user;
    in.open(fileName);
    if(in.is_open())
    {
        for(int i = 0; !in.eof(); i++)
        {
            in >> user;
            users.push_back(user);
            ID = user.getID();
        }
        //std::cout << "<script> alert(\"Successfully loaded users.dat!\"); </script>" << std::endl;
        // sometimes we get duplicates, remove them
        if(users[users.size()-1] == users[users.size()-2])
            users.pop_back();
    }
    else
        std::cout << "<script> alert(\"Cannot open " << fileName << "!. Cannot load users into system.\")</script>" << std::endl;
    in.close();
    if(in.is_open())
    {
        std::cout << "<script> alert(\"" << fileName << " did not close properly. Trying again...\")</script>" << std::endl;
        in.close();
    }
}