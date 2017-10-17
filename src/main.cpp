#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "user.hpp"
#include "task.hpp"
#include "util.hpp"

const char *usersDat = "/var/www/data/users.dat";
const char *tasksDat = "/var/www/data/tasks.dat";

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
    bool success = false;
    std::string userName = getValue("username", formdata);
    std::string password = getValue("password", formdata);
    for(auto iter = users.begin(); iter != users.end(); ++iter)
    {
        if(iter->getUsername() == userName && iter->getPassword() == password)
        {
            success = true;
            std::string id = std::to_string(iter->getID());
            //std::cout << "<script> alert(\"Login was successful!\"); </script>" << std::endl;
            // document.cookie = "username" + "=" + username;
            // document.cookie = "userID" + "=" + id;
            std::cout << "<script> document.cookie = \"username\" + \"=\" + \"" << userName << "; path=/;\"; </script>";
            std::cout << "<script> document.cookie = \"userID\" + \"=\" + \"" << id << "; path=/;\";</script>";
        }
    }
    if(!success)
        std::cout << "<script> alert(\"Failed to login. Check your credentials and try again\");</script>"<<std::endl;

}

int main(void)
{
    cgicc::Cgicc formdata;
    
    std::vector<User> users;
    std::vector<Task> tasks;
    std::cout << cgicc::HTTPHTMLHeader() << std::endl;
    std::string form;
    form = checkFormType(formdata);
    loadUsers(users, usersDat);
    loadTasks(tasks, tasksDat);
    if(form.compare("Create User") == 0)
    {
        User user;
        user.createUser(formdata);
        user.saveUser(usersDat);
        users.push_back(user);
    }
    else if(form.compare("Create Task") == 0)
    {
        Task task;
        task.createTask(formdata);
        task.saveTask(tasksDat);
        tasks.push_back(task);
    }
    else if(form.compare("Login") == 0)
    {
        login(formdata, users);
    }
    else if(form.compare("Search") == 0)
    {
        std::cout << "<script> alert(\"Search yet to be implemented...\");</script>" << std::endl;
        //search(formdata);
    }
    goBack();
    return 0;
}