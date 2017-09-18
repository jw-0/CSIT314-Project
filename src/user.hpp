#pragma once
#include <cgicc/Cgicc.h>
#include <string>
#include <fstream>
struct Location
{
    std::string country;
    std::string state;
    std::string city;
};

std::string getValue(const char *valueName, cgicc::Cgicc formdata);

class User
{
    public:
        void createUser(cgicc::Cgicc formdata);
        void saveUser(const char *filename);
        void loadUser(const char *filename);
        std::ostream &displayUser(std::ostream &);
    private:
        std::string username;
        std::string firstName;
        std::string lastName;
        std::string service;
        std::string offerDate;
        std::string endDate;
        std::string email;
        std::string location; // TODO: Change to Location struct when input forms are more mature 

};
