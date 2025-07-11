#include "../cub3d_parsing.h"
//floating pt remainder ie keep between 0 and 2pi for our calcs 
//keep remainder of angle / 2pi
float normalize_angle(float angle)
{
    angle = fmod(angle, TWO_PI);
    if (angle < 0)
        angle += TWO_PI;
    return angle;
}

// Purpose: Euclidean distance from player to wall hit.
// ie shortest dir distance from pythagorean theorm
float hit_distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
