#include "cub3d_parsing.h"

/* Copies data from prev col if two distances tie ie same distanc */
static void copy_last_ray(t_ray *rays, int col)
{
    t_ray *curr = &rays[col];
    t_ray *prev = &rays[col - 1];
    *curr = *prev;  // struct copy: angle, dist, hit[], wall_content, flags...
}

/*
 Fires one ray at a given angle from the player's position.
 fish-eye correction to keep walls from looking warped.
collission returns where the ray first hits a wall horizontally and then verticaly
these fill out t_cast structs 
Rays farther from the center of the screen travel at an angle — 
without correction, those walls look stretched.
cos(...) scales the distance to correct that — 
this way, walls appear vertically aligned even if the ray is at an angle.

no hit infinity otelse we calc  distance between player n hit point Pythag 
 corrected for fish-eye.
Store the result into the ray buffer (rays[col]) so rendering code knows what to draw.
 one ray result per screen column.
The vertical_hit flag is important for later:
Shade vertical walls darker Pick the right tex(e.g., N wall vs E wall)
 */
static void cast_ray(t_cub_elements  *app, float angle, int col, t_ray *rays)
{
    t_cast h, v;
    find_horizontal_collision(&app->map, &app->player, angle, &h);
    find_vertical_collision  (&app->map, &app->player, angle, &v);

    float fish_eye = cos(app->player.angle - angle);
    if (!h.hitted) h.distance = INFINITY;
    else           h.distance = hit_distance(app->player.x, app->player.y, h.hit[X], h.hit[Y]) * fish_eye;
    if (!v.hitted) v.distance = INFINITY;
    else           v.distance = hit_distance(app->player.x, app->player.y, v.hit[X], v.hit[Y]) * fish_eye;

    if (h.distance < v.distance)
    {
        store_ray_data(&rays[col], &h, angle, /*vertical_hit=*/false);
    }
    else if (v.distance < h.distance)
    {
        store_ray_data(&rays[col], &v, angle, /*vertical_hit=*/true);
    }
    else if (col > 0)
    {
        copy_last_ray(rays, col);
    }
}

/* Cast a ray for each column across the screen 
If their FOV is 60 degrees, then:

They can see 30 degrees to the left

And 30 degrees to the right of A
angle = π/2 - π/6 = π/3      // left-most ray
         ↑
         |
        /
       /     ← rays go from here ...
      /
     •────────→ π/2 ← straight ahead
      \
       \     ← ... to here
        \
         ↓
      π/2 + π/6 = 2π/3        // right-most ray

ach ray_step moves you a tiny bit to the right, until you sweep from left to right across the whole FOV.


*/
void raycasting(t_cub_elements  *app, t_ray *rays)
{
    float angle = app->player.angle - HALF_FOV;
    for (int col = 0; col < app->mlx.width; col++, angle += app->player.ray_step)
    {
        angle = normalize_angle(angle);
        cast_ray(app, angle, col, rays);
    }
}

/*
The corrected distance to the wall
The exact hit coordinates
What type of wall you hit (e.g., '1' or texture ID)
*/

void store_ray_data(t_ray *ray, t_cast *cast, float angle, bool vertical)
{
    ray->angle = angle;
    ray->dist = cast->distance;
    ray->hit[X] = cast->hit[X];
    ray->hit[Y] = cast->hit[Y];
    ray->wall_content = cast->content;
    ray->vertical_hit = vertical;
}