#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "user.hpp"
#include "task.hpp"
#include "util.hpp"
#include "transactions.hpp"
#include "debug.hpp"

const char *usersDat = "/var/www/data/users.dat";
const char *tasksDat = "/var/www/data/tasks.dat";
const char *transDat = "/var/www/data/trans.dat";
const char *tempFile = "/var/www/data/temp";

std::string headerStr = "<table border=0 width=\"100%\"><tr><th colspan=3 style=\"border-bottom: 1px solid;\"/></tr>\n";
std::string titleStr = "<tr><td width=\"60%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>Title: </b> </td></tr>\n";
std::string priceStr = "<td width=\"40%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>Price: $</b> </td></tr>\n";
std::string dueStr = "<tr><td width=\"100%\" style=\"text-align:left; font-family:Calibri; padding: 5px 0px; font-size: 16px;\"><b>Due: </b> </td></tr>\n";
std::string locStr = "<tr><td width=\"100%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>Location: </b> </td></tr>\n";
std::string descStr = "<tr><td width=\"100%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>Description: </b> </td></tr>\n";
std::string userStr = "<tr><td width=\"100%\" style=\"text-align:left; font-family:Calibri; padding: 15px 0px; font-size: 16px;\"><b>Offering User: </b> </td></tr>\n";
std::string bottomStr = "<tr><th colspan=3 style=\"border-bottom: 1px solid;\"/></tr></table>";
std::string backButton = "<button onclick=window.history.back()> Go Back </button>";
std::string buyButton1 = "<form action=\"/cgi-bin/csit314.cgi\" method=\"post\"><input id=\"purchase\" type=\"hidden\" name=\"purchase\" value=\"purchase\"><input id=\"offererID\" type=\"hidden\" name=\"offererID\" value=\"\">";
std::string buyButton2 = "<input id=\"serviceNum\" type=\"hidden\" name=\"serviceNum\" value=\"\">";
std::string buyButton3 = "<input id=\"responderID\" type=\"hidden\" name =\"responderID\" value=\"\"><input type=\"submit\" value=\"Purchase\"></form>";

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

std::string getUserByID(long id, std::vector<User> users)
{
    for(auto iter = users.begin(); iter != users.end(); ++iter)
    {
        if(id == iter->getID())
            return iter->getUsername();
    }
    return "null";
}

void deleteTask(cgicc::Cgicc formdata, std::vector<Task> &tasks, std::vector<User> users)
{
    std::string title = getValue("title", formdata);
    std::ofstream temp;
    temp.open(tempFile, std::ofstream::out | std::ofstream::trunc);
    bool success = false;
    for(auto iter = tasks.begin(); iter != tasks.end(); ++iter)
    {
        temp << iter->getTitle() << "\t" << title << std::endl;
        if(iter->getTitle() == title)
        {
            if(iter == tasks.end())
            {
                alert("POP!");
                tasks.pop_back();
            }
            else
                tasks.erase(iter);
            alert("Successfully deleted task");
            success = true;
            break;
        }
        else if(iter->getTitle() == "")
            tasks.erase(iter);
    }
    if(!success)
        alert("Could not delete task.");
    //saveTasks(tasks, tasksDat);
    temp.close();
}

void purchase(cgicc::Cgicc formdata, std::vector<Task> tasks, std::vector<User> users, std::vector<Transaction> &transactions)
{
    std::string title = getValue("title", formdata);
    std::string responderID = getValue("responderIDPurchase", formdata);
    alert(getValue("responderIDPurchase", formdata));
    alert(responderID);
    Transaction transaction;
    bool success = false;
    for(auto iter = tasks.begin(); iter != tasks.end(); ++iter)
    {
        if(iter->getTitle() == title)
        {
            int oi = std::stoi(iter->getOwnerID(), nullptr, 0);
            int ri = std::stoi(responderID, nullptr, 0);
            int sn = std::stoi(iter->getServiceNum(), nullptr, 0);
            transaction.createTransaction(ri, oi, sn);
            transaction.saveTransaction(transDat);
            transactions.push_back(transaction);
            success = true;
            alert("Successfully purchased!");
            break;
        }
    }
    if(!success)
        alert("Could not find that service. Transaction not processed.");

}

void search(cgicc::Cgicc formdata, std::vector<Task> tasks, std::vector<User> users)
{
    std::string title = getValue("title", formdata);
    std::string responderID = getValue("responderID", formdata);
    int length = 0;
    bool success = false;
    std::ofstream temp;
    temp.open(tempFile);
    for(auto iter = tasks.begin(); iter != tasks.end(); ++iter)
    {
        if(iter->getTitle() == title)
        {
            titleStr.insert(116, iter->getTitle());
            priceStr.insert(113, iter->getOfferPrice());
            dueStr.insert(114, iter->getDeadline());
            locStr.insert(120, iter->getLocation());
            descStr.insert(123, iter->getDescription());
            userStr.insert(125, getUserByID(std::stoi(iter->getOwnerID(), nullptr, 0), users));
            buyButton1.insert(178, iter->getOwnerID());
            buyButton2.insert(62, iter->getServiceNum());
            buyButton3.insert(65, responderID);
            temp << buyButton1 << std::endl << buyButton2 << std::endl << buyButton3 << std::endl;
            std::cout << headerStr << titleStr << priceStr << dueStr << locStr << descStr << userStr << bottomStr << backButton << std::endl;
            success = true;
        }
    }
    if(!success)
    {
        std::string msg= "Could not find ";
        msg.append(title);
        alert(msg);
    }
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
            #ifdef DEBUG
            alert("Login was successful!");
            #endif
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
    std::vector<Transaction> transactions;
    std::cout << cgicc::HTTPHTMLHeader() << std::endl;
    std::string form;
    form = checkFormType(formdata);
    loadUsers(users, usersDat);
    loadTasks(tasks, tasksDat);
    loadTransactions(transactions, transDat);
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
        search(formdata, tasks, users);
    }
    else if(form.compare("delete") == 0)
    {
        deleteTask(formdata, tasks, users);
        alert("Going back!");
        goBack();
    }
    else if(form.compare("Purchase") == 0)
    {
         purchase(formdata, tasks, users, transactions);
    }

    if(form.compare("Search") != 0)
        goBack();
    return 0;
}