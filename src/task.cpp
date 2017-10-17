#include <iostream>
#include <fstream>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "util.hpp"
#include "task.hpp"

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
    active = true;
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
        //std::cout << "<script> alert(\" Successfully wrote task!\"); </script>" << std::endl;
    }
    else
        std::cout << "<script> alert(\"Cannot open " << fileName << "!\")</script>" << std::endl;
    out.close();
}

std::istream &operator>>(std::istream &in, Task &task)
{
    std::string boolVal;
    in >> task.serviceNum >> task.title >> task.offerPrice >> task.deadline >> task.location >> task.imgLink >> task.description >> task.ownerID >> boolVal;
    if(boolVal.compare("true") == 0)
        task.active = true;
    else
        task.active = false;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Task &task)
{
    std::string boolVal = task.active == true ? "true" : "false";
    out << task.serviceNum << "\t" << task.title << "\t" << task.offerPrice << "\t" << task.deadline << "\t" << task.location << "\t" << task.imgLink << "\t" << task.description << "\t" << task.ownerID << "\t" << boolVal << std::endl;
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
        //std::cout << "<script> alert(\"Successfully loaded tasks.dat!\"); </script>" << std::endl;
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