// Written by Jarod Wright
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

class Transaction
{
public:
    void createTransaction(cgicc::Cgicc formdata);
    void saveTransaction(const char *);
    void createTransaction(int ri, int oi, int sn)
    {
        responderID = ri;
        offererID = oi;
        serviceNum = sn;
    }
    int getResponderID() { return responderID; }
    int getOffererID() { return offererID; }
    int getServiceNum() { return serviceNum; }
    friend std::ostream &operator<<(std::ostream &, const Transaction &);
    friend std::istream &operator>>(std::istream &, Transaction &);
private:
    int responderID;
    int offererID;
    int serviceNum;
};

void loadTransactions(std::vector<Transaction> &, const char *);
void saveTransactions(std::vector<Transaction>, const char *);