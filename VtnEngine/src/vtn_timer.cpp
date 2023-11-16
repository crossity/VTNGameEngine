#include <time.h>

#include "vtn_timer.hpp"
#include "vtn_types.hpp"

double vtn_sync_time, vtn_delta_time, vtn_fps;
int vtn_is_pause = 0;

void vtnTimer( void )
{
  int64 t;
  static int64 start_time = -1, old_time, pause_time = 0, fps_time, frame_count;

  t = clock();
  if (start_time == -1)
    start_time = old_time = fps_time = t;
  if (vtn_is_pause)
  {
    vtn_delta_time = 0;
    pause_time += t - old_time;
  }
  else
  {
    vtn_delta_time = (t - old_time) / (double)CLOCKS_PER_SEC;
    vtn_sync_time = (t - pause_time - start_time) / (double)CLOCKS_PER_SEC;
  }
  frame_count++;
  if (t - fps_time > 3 * CLOCKS_PER_SEC)
  {
    vtn_fps = frame_count / ((t - fps_time) / (double)CLOCKS_PER_SEC);
    fps_time = t;
    frame_count = 0;
  }
  old_time = t;
}