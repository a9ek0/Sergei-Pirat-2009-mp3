#include "chrono.h"

char* get_current_time() {
    time_t now = time(NULL);
    struct tm t;
    localtime_s(&t, &now);
    static char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H.%M.%S", &t);
    return buf;
}