// Original code based off code found here: https://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm
// (With heavy original modifications)
#include <iostream>
#include <vector>
#include <string>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

void outputValue(const char *valueName, cgicc::Cgicc formdata)
{
    auto iter = formdata.getElement(valueName);
    std::cout << "<br/>\n";
    if(!iter->isEmpty() && iter != (*formdata).end())
        std::cout << valueName << ": " << **iter << std::endl;
    else
        std::cout << "No data entered (" << valueName << ")" << std::endl;
}

int main(void)
{
    cgicc::Cgicc formdata;
    // With cgi when we write to stdout it gets directed into the web page
    std::cout << cgicc::HTTPHTMLHeader() << std::endl; 
    std::cout << "<html>\n";
    std::cout << "<head>\n";
    std::cout << "<title> Collected data from form</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";
    outputValue("username", formdata);
    outputValue("firstName", formdata);
    outputValue("lastName", formdata);
    outputValue("service", formdata);
    outputValue("offerDate", formdata);
    outputValue("endDate", formdata);
    outputValue("email", formdata);
    std::cout << "<br/>";
    std::cout << "</body>\n";
    std::cout << "</html\n";

     return 0;
}
    

