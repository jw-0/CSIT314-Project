#include <iostream>
#include <memory>
#include "fcgio.h"
// First round of code from here: http://chriswu.me/blog/writing-hello-world-in-fcgi-with-c-plus-plus/

int main()
{
    // Backup cin and cout streambuffers, this is just so we can return to normal cin
    // and cout operation after we're done using them to stream data to the web page
    std::streambuf *cin_streambuf = std::cin.rdbuf();
    std::streambuf *cout_streambuf = std::cout.rdbuf();
    std::streambuf *cerr_streambuf = std::cerr.rdbuf();

    FCGX_Request request;
    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);
    while(FCGX_Accept_r(&request) == 0)
    {
        // We will use these buffers to read and write data to the webpage
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);
        // We bind them here
        std::cin.rdbuf(&cin_fcgi_streambuf);
        std::cout.rdbuf(&cout_fcgi_streambuf);
        std::cerr.rdbuf(&cerr_fcgi_streambuf);

        std::cout << "Content-type: text/html\r\n"
             << "\r\n"
             << "<html>\n"
             << "    <head>\n"
             << "        <title> Hello, World!</title>\n"
             << "    </head>"
             << "    <body>\n"
             << "        <h1> Test </h1>\n"
             << "    </body>\n"
             << "</html>\n";
    }
    // Restor the original streams
    std::cin.rdbuf(cin_streambuf);
    std::cout.rdbuf(cout_streambuf);
    std::cerr.rdbuf(cerr_streambuf);

    return 0;
}
