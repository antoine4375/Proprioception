#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <time.h>

#include <boost/date_time/local_time/local_time.hpp>

class LogerMsg
{
public:
	LogerMsg();
	~LogerMsg();

    LogerMsg(std::string name);
    void writeLog(std::string msg);

private:
    std::vector<std::string> message_;
    std::string path_;
    std::string unitName_, fileName_;
    boost::local_time::local_time_facet *day_facet;
    boost::local_time::local_time_facet *daytime_facet;
};

