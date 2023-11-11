#include <time.h>

#include "vtn_timer.hpp"
#include "vtn_types.hpp"

float vtn_delta_time;

void vtnTimer() {
    static uint64 t, start_time = - 1;

    t = clock();

    if (start_time == -1)
        vtn_delta_time = (start_time = t) / (double)CLOCKS_PER_SEC;
    
    if (start_time != t) {
        vtn_delta_time = (t - start_time) / (double)CLOCKS_PER_SEC;
        start_time = t;
    }
}