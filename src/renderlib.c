#include <stdio.h>
#include "../include/renderlib.h"
#include <math.h> // TODO  i should prolly just use the pi from this?


// render
/*

  for all points in scene
    if (point.z > viewport.z)
      get line from eye coord to point
      check intersection
      if intersection is in range of viewport (left edge < x < right edge; same for y)
        renderable; convert to pixel and save it to canvas accessible


*/
