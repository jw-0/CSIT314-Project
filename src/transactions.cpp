// Written by Jarod Wright
#include "transactions.hpp"
#include <vector>
#include <fstream>
#include "util.hpp"
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

std::ostream &operator<<(std::ostream &out, const Transaction &t)
{
    out << t.responderID << "\t" << t.offererID << "\t" << t.serviceNum << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Transaction &t)
{
    in >> t.responderID >> t.offererID >> t.serviceNum;
    return in;
}

void Transaction::createTransaction(cgicc::Cgicc formdata)
{
    responderID = std::stoi(getValue( "responderID", formdata), nullptr, 0);
    offererID = std::stoi(getValue("offererID", formdata), nullptr, 0);
    serviceNum = std::stoi(getValue("serviceNum", formdata), nullptr, 0);
}

void Transaction::saveTransaction(const char *fileName)
{
    std::ofstream out;
    out.open(fileName, std::ofstream::app);
    if(out.is_open())
        out << *this;
    out.close();
}

void loadTransactions(std::vector<Transaction> &t, const char *fileName)
{
    std::ifstream in;
    Transaction trans;
    in.open(fileName);
    if(in.is_open())
    {
        for(int i = 0; !in.eof(); i++)
        {
            in >> trans;
            t.push_back(trans);
        }
    }
    else
        alert("Could not open transactions.dat");
    in.close();
}

void saveTransactions(std::vector<Transaction> t, const char *fileName)
{
    std::ofstream out;
    out.open(fileName);
    if(out.is_open())
    {
        for(auto iter = t.begin(); iter != t.end(); ++iter)
            out << *iter;
    }
    out.close();
}
