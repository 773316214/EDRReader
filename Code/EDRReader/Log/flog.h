/****************************************************************************
**
** Copyright (C) 2022 EDRReader
**
** Version	: 1.0.0
** Author	: DuanZhaobing
** Email    : duanzb@waythink.cn
** Data     : 2022.06.06-2022.06.06
**
****************************************************************************/

#ifndef LOG_H
#define LOG_H
#include "Log/src/easylogging++.h"

class LogHandler : public el::LogDispatchCallback {
public:
    void handle(const el::LogDispatchData* data);
};

class HtmlHandler : public el::LogDispatchCallback {
public:
    HtmlHandler();
    void handle(const el::LogDispatchData* data);
};


#endif // LOG_H

