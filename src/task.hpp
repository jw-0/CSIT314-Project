#pragma once

static int ServiceNum = 0;

class Task
{
    public:
        void createTask(cgicc::Cgicc formdata);
        std::istream &loadTask(std::istream &);
        void saveTask(const char *);
        friend std::istream &operator>>(std::istream &, Task &);
        friend std::ostream &operator<<(std::ostream &, const Task &);
        friend bool operator==(const Task &lhs, const Task &rhs);

        // simple getters
        std::string getServiceNum()        { return serviceNum; }
        std::string getTitle()      { return title; }
        std::string getOfferPrice() { return offerPrice; }
        std::string getDeadline()   { return deadline; }
        std::string getLocation()   { return location; }
        std::string getImgLink()    { return imgLink; }
        std::string getDescription(){ return description; }
        std::string getOwnerID()    { return ownerID; }
        bool isActive()             { return active; }
    private:
        std::string serviceNum;
        std::string title;
        std::string offerPrice;
        std::string deadline;
        std::string location;
        std::string imgLink;
        std::string description;
        std::string ownerID;
        bool active;
};

void loadTasks(std::vector<Task> &tasks, const char *fileName);