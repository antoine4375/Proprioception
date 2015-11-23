#include "StdAfx.h"
#include "LogerMsg.h"

#include <fstream>
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"

LogerMsg::LogerMsg()
{
	LogerMsg("C:\\Users\\taehwan\\Documents\\MATLAB\\VisuoHaptic\\log.txt");
}

LogerMsg::LogerMsg(std::string name) : unitName_(name)
{
    path_ = unitName_;
    boost::filesystem::path p(path_);
    boost::system::error_code err;

    message_.clear();
}


LogerMsg::~LogerMsg()
{
}

void LogerMsg::writeLog(std::string msg)
{
    std::stringstream stream;

    stream << msg << std::endl;
    message_.push_back(stream.str());

    if (message_.size() >= 1)
    {
        std::ofstream outputFile;
        outputFile.open("C:\\Users\\taehwan\\Documents\\MATLAB\\VisuoHaptic\\log.txt",std::ios_base::out | std::ios_base::app);
        for (int i = 0; i < message_.size(); i++)
        {
            outputFile << message_[i];
        }
        message_.clear();
//        while (!message_.empty())
//        {
//            outputFile << message_.front();
//            message_.pop_front();
//        }
        outputFile.close();
    }
}

