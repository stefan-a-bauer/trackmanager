#include "Exception.h"

Exception::Exception(const std::string &what_arg) :
    runtime_error(what_arg)
{
}

Exception::Exception(const char *what_arg) :
    runtime_error(what_arg)
{
}

Exception::Exception(const QString &what_arg) :
    Exception(what_arg.toStdString())
{
}

Exception::~Exception()
{
}
