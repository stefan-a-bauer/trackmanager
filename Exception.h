#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <QString>

class Exception : public std::runtime_error
{
public:
    Exception(const std::string &what_arg);
    Exception(const char *what_arg);
    Exception(const QString &what_arg);
    virtual ~Exception();
};

#endif
