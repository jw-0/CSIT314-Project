#pragma once
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

std::string getValue(const char *valueName, cgicc::Cgicc formdata);