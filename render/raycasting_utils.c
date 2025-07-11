#include "cub3d_parsing.h"
//basically each quater circle is pi/2 the one on the right is 0 or 2pi
//defining dir of ray 
bool is_ray_facing(int dir, float angle)
{
    if (dir == NORTH)
        return angle > PI && angle < TWO_PI;
    if (dir == SOUTH)
        return !is_ray_facing(NORTH, angle);
    if (dir == WEST)
        return angle > HALF_PI && angle < 1.5 * PI;
    if (dir == EAST)
        return !is_ray_facing(WEST, angle);
    return false;
}