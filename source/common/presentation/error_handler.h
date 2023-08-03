#ifndef _COMMON_PRESENTATION_ERROR_HANDLER_H_
#define _COMMON_PRESENTATION_ERROR_HANDLER_H_

#include <httplib/httplib.h>

#include "../domain/app_error.h"

void handleAppError(AppError &error, httplib::Response &res);

#endif
