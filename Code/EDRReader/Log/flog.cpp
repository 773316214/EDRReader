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
#include "Log/flog.h"

INITIALIZE_EASYLOGGINGPP

void LogHandler::handle(const el::LogDispatchData* data) {
    // NEVER LOG ANYTHING HERE! NOT HAPPY WITH MULTI_THREADING
    ELPP_COUT << "Test this " << data << std::endl;
}

HtmlHandler::HtmlHandler() {
    el::Loggers::getLogger("html");
}
void HtmlHandler::handle(const el::LogDispatchData* data) {
    // NEVER LOG ANYTHING HERE! NOT HAPPY WITH MULTI_THREADING
    ELPP_COUT << "<b>" << data->logMessage()->message() << "</b>" << std::endl;
}
