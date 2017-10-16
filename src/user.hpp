#pragma once
#include <cgicc/Cgicc.h>
#include <string>
#include <fstream>
#include <vector>

std::string getValue(const char *valueName, cgicc::Cgicc formdata);

static int ID = 0;

class User
{
    public:
        User();
        void createUser(cgicc::Cgicc formdata);
        std::istream &loadUser(std::istream &);
        void saveUser(const char *);
        friend std::istream &operator>>(std::istream &, User &);
        friend std::ostream &operator<<(std::ostream &, const User &);
        friend bool operator==(const User &lhs, const User &rhs);
        // simple getters
        int getID() { return id; }
        std::string getUsername() { return username; }
        std::string getPassword() { return password; }
        std::string getFirstName() { return firstName; }
        std::string getLastName() { return lastName; }
        std::string getEmail() { return email; }
        std::string getPhone() { return phone; }
    private:
        int id;
        std::string username;
        std::string firstName;
        std::string lastName;
        std::string email;
        std::string phone;
        std::string password;
        float rating;
};

void loadUsers(std::vector<User> &, const char *);