#pragma once

class Task
{
    public:
        void createUser(cgicc::Cgicc formdata);
        std::istream &loadUser(std::istream &);
        void saveUser(const char *);
        friend std::istream &operator>>(std::istream &, User &);
        friend std::ostream &operator<<(std::ostream &, const User &);
        friend bool operator==(const User &lhs, const User &rhs);
        // simple getters
        int getID() { return id; }
        std::string get() { return ; }
        std::string get() { return ; }
        std::string get() { return ; }
        std::string get() { return ; }
        std::string get() { return ; }
        std::string get() { return ; }
    private:
};