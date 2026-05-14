#ifndef LOG_H
#define LOG_H

#include <string>
#include <memory>
#include <deque>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
enum LogLevel { LOG_NORMAL, LOG_REMARK, LOG_ERROR };

class Log {
public:
    static Log* Instance();
    void message(LogLevel level, const std::string& msg);
    void print() const;

    ~Log();
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

private:
    Log();
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

#endif