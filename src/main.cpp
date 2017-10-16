#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "user.hpp"
const char *usersDat = "/var/www/data/users.dat";

void goBack()
{
    std::cout << "<script>  window.history.back();  </script>" << std::endl;
}

// Checks the type of form, and changes what we do with the data accordingly
auto checkFormType(cgicc::Cgicc formdata)
{
    std::string form = "null";
    const char* valueName = "formType";
    auto iter = formdata.getElement(valueName);
    
    if(!iter->isEmpty() && iter != (*formdata).end())
        form = **iter;
    return form;
}

// traverse the users vector, check our username and password, create a cookie if successful.
void login(cgicc::Cgicc formdata, std::vector<User> &users)
{
    //loadUsers(users, usersDat);
    std::string userName = getValue("username", formdata);
    std::string password = getValue("password", formdata);
    for(auto iter = users.begin(); iter != users.end(); ++iter)
    {
        if(iter->getUsername() == userName && iter->getPassword() == password)
        {
            std::cout << "<script> alert(\"Login was successful!\"); window.history.back(); </script>" << std::endl;
            std::cout << cgicc::HTTPHTMLHeader().setCookie(cgicc::HTTPCookie("username", userName));
        }
    }
}

int main(void)
{
    cgicc::Cgicc formdata;
    
    std::vector<User> users;
    //std::vector<Task> tasks;
    std::cout << cgicc::HTTPHTMLHeader() << std::endl;
    std::string form;
    form = checkFormType(formdata);
    loadUsers(users, usersDat);
    if(form.compare("null") == 0)
    {
        std::cout << "<script> alert(\"This shouldn't ever happen...\");window.history.back();</script>" << std::endl;
    }
    else if(form.compare("Create User") == 0)
    {
        User user;
        user.createUser(formdata);
        user.saveUser(usersDat);
        users.push_back(user);
    }
    else if(form.compare("Create Task") == 0)
    {
        std::cout << "<script> alert(\"Create task yet to be implemented...\");window.history.back();</script>" << std::endl;
        //createTask(formdata);
    }
    else if(form.compare("Login") == 0)
    {
        //std::cout << "<script> alert(\"Login yet to be implemented...\");window.history.back();</script>" << std::endl;
        login(formdata, users);
    }
    else if(form.compare("Search") == 0)
    {
        std::cout << "<script> alert(\"Search yet to be implemented...\");window.history.back();</script>" << std::endl;
        //search(formdata);
    }
    goBack();
    return 0;
}