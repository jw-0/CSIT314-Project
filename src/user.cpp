// Written by Jarod Wright

#include "user.hpp"
#include <fstream>
#include <cgicc/HTMLClasses.h>
#include "util.hpp"
#include "debug.hpp"

static std::string headerStr = "<table border=0 width=\"100%\"><tr><th colspan=3 style=\"border-bottom: 1px solid;\"/></tr>\n";
static std::string usernameStr = "<tr><td width=\"60%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>Username: </b> </td></tr>\n";
static std::string fnStr = "<td width=\"40%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>First Name: $</b> </td></tr>\n";
static std::string lnStr = "<tr><td width=\"100%\" style=\"text-align:left; font-family:Calibri; padding: 5px 0px; font-size: 16px;\"><b>Last Name: </b> </td></tr>\n";
static std::string emailStr = "<tr><td width=\"100%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>E-Mail: </b> </td></tr>\n";
static std::string phone = "<tr><td width=\"100%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>Phone: #</b> </td></tr>\n";
static std::string rating = "<tr><td width=\"100%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>Rating: </b> </td></tr>\n";
static std::string bottomStr = "<tr><th colspan=3 style=\"border-bottom: 1px solid;\"/></tr></table>";
static std::string backButton = "<button onclick=window.history.back()> Go Back </button>";

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
    rating = 5.0;
}

void viewUser(cgicc::Cgicc formdata, std::vector<User> users)
{
    std::string id = getValue("userID", formdata);
    bool success = false;
    for(auto iter = users.begin(); iter != users.end(); ++iter)
    {
        /* username 119
        fname 118
        lname 120
        email 118
        p 118
        r 118
        */
        if(iter->getID() == std::stoi(id, nullptr, 0))
        {
            usernameStr.insert(119, iter->getUsername());
            fnStr.insert(118, iter->getFirstName());
            lnStr.insert(120, iter->getLastName());
            emailStr.insert(118, iter->getEmail());
            phone.insert(118, iter->getPhone());
            rating.insert(118, std::to_string(iter->getRating()));
            std::cout << headerStr << usernameStr << fnStr << lnStr << emailStr << phone << rating << bottomStr << backButton << std::endl;
            success = true;
        }
    }
    if(!success)
        alert("Problem viewing user profile.");
}

void User::saveUser(const char *fileName)
{
    std::ofstream out;
    out.open(fileName, std::ofstream::app);
    if(out.is_open())
    {
        out << *this;
        #ifdef DEBUG
        std::cout << "<script> alert(\" Successfully wrote user! \"); </script>" << std::endl;
        #endif
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
    in >> user.id >> user.username >> user.firstName >> user.lastName >> user.email >> user.phone >> user.password >> user.rating;
    return in;
}

std::ostream &operator<<(std::ostream &out, const User &user)
{
    out << user.id << "\t" << user.username << "\t" <<  user.firstName << "\t" << user.lastName << "\t" << user.email << "\t" << user.phone << "\t" << user.password << "\t"<< user.rating << std::endl;;
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
        #ifdef DEBUG
        std::cout << "<script> alert(\"Successfully loaded users.dat!\"); </script>" << std::endl;
        #endif
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