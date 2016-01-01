#ifndef TYPES_H
#define TYPES_H

#include <QtGlobal>

// in SQLite, primary keys are always 64 bit signed integers (https://www.sqlite.org/autoinc.html)
typedef qint64 pkey_t;

#endif
