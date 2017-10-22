#pragma once
#include <string>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

std::string getValue(const char *valueName, cgicc::Cgicc formdata);
void alert(std::string msg);