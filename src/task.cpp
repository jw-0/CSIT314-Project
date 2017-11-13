// Written by Jarod Wright
#include <iostream>
#include <fstream>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cstdlib>
#include "util.hpp"
#include "task.hpp"
#include "debug.hpp"

void Task::createTask(cgicc::Cgicc formdata)
{
    title = getValue("title", formdata);
    location = getValue("location", formdata);
    description = getValue("description", formdata);
    offerPrice = getValue("offeringPrice", formdata);
    deadline = getValue("deadline", formdata);
    ServiceNum += 1;
    serviceNum = std::to_string(ServiceNum);
    ownerID = getValue("userid", formdata);
    imgLink = "http://dummysite.com/img";
    flagLevel = "1";
    rating = 5.0;
    active = true;
    alert("Successfully created task!");
}

std::istream &Task::loadTask(std::istream &in)
{
    in >> *this;
    return in;
}

void Task::saveTask(const char *fileName)
{
    std::ofstream out;
    out.open(fileName, std::ofstream::app);
    if(out.is_open())
    {
        out << *this;
        #ifdef DEBUG
        std::cout << "<script> alert(\" Successfully wrote task!\"); </script>" << std::endl;
        #endif
    }
    else
        std::cout << "<script> alert(\"Cannot open " << fileName << "!\")</script>" << std::endl;
    out.close();
}

std::istream &operator>>(std::istream &in, Task &task)
{
    std::string boolVal;
    in >> task.serviceNum >> task.title >> task.offerPrice >> task.deadline >> task.location >> task.imgLink >> task.description >> task.flagLevel >> task.ownerID >> boolVal >> task.rating;
    ServiceNum = std::stoi(task.serviceNum, nullptr, 0);
    if(boolVal.compare("true") == 0)
        task.active = true;
    else
        task.active = false;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Task &task)
{
    std::string boolVal;
    if(task.active)
        boolVal = "true";
    else
        boolVal = "false";
    out << task.serviceNum << "\t" << task.title << "\t" << task.offerPrice << "\t" << task.deadline << "\t" << task.location << "\t" << task.imgLink << "\t" << task.description << "\t" << task.flagLevel << "\t" << task.ownerID << "\t" << boolVal << "\t" << task.rating<< std::endl;
    return out;
}

bool operator==(const Task &lhs, const Task &rhs)
{
    if(lhs.serviceNum == rhs.serviceNum && 
       lhs.title == rhs.title &&
       lhs.offerPrice == rhs.offerPrice &&
       lhs.deadline == rhs.deadline &&
       lhs.location == rhs.location &&
       lhs.description == rhs.description &&
       lhs.ownerID == rhs.ownerID)
        return true;
    return false;
}

Task Task::operator=(const Task &rhs)
{
    serviceNum = rhs.serviceNum; 
    title = rhs.title;
    offerPrice = rhs.offerPrice;
    deadline = rhs.deadline;
    location = rhs.location;
    description = rhs.description;
    ownerID = rhs.ownerID;
    rating = rhs.rating;
    return *this;
}

void saveTasks(std::vector<Task> tasks, const char *fileName)
{
    std::ofstream out;
    out.open(fileName);
    if(out.is_open())
    {
        for(auto iter = tasks.begin(); iter != tasks.end(); ++iter)
        {
            out << *iter;
        }
        out << std::endl;
    }
    out.close();
}

void loadTasks(std::vector<Task> &tasks, const char *fileName)
{
    std::ifstream in;
    Task task;
    in.open(fileName);
    if(in.is_open())
    {
        for(int i = 0; !in.eof(); i++)
        {
            in >> task;
            tasks.push_back(task);
        }
        #ifdef DEBUG
        std::cout << "<script> alert(\"Successfully loaded tasks.dat!\"); </script>" << std::endl;
        #endif
        // sometimes we get duplicates, remove them
        if(tasks[tasks.size()-1] == tasks[tasks.size()-2])
            tasks.pop_back();
    }
    else
        std::cout << "<script> alert(\"Cannot open " << fileName << "!. Cannot load tasks into system.\")</script>" << std::endl;
    in.close();
    if(in.is_open())
    {
        std::cout << "<script> alert(\"" << fileName << " did not close properly. Trying again...\")</script>" << std::endl;
        in.close();
    }
}