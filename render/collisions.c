#include "cub3d_parsing.h"


  // Calc how far to step for each next horizontal gridline intersection
float calculate_y_intercept(t_player *player, t_map *map, float angle)
{
    int tile_y = floor(player->y / map->tile_size) * map->tile_size;
    if (is_facing_north(angle))
        return tile_y - 0.0001f;
    else
        return tile_y + map->tile_size;
}

static void trace_horizontal_ray(t_map *map, t_ray_step *step, t_cast *h)
{
    while (1)
    {
        int map_x = (int)(step->next_x) / map->tile_size;
        int map_y;

        if (step->facing_north)
            map_y = ((int)(step->next_y) - 1) / map->tile_size;
        else
            map_y = (int)(step->next_y) / map->tile_size;

        if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
        {
            h->hitted = false;
            return;
        }
        if (map->map[map_y][map_x] == '1')
        {
            h->hit[X] = step->next_x;
            h->hit[Y] = step->next_y;
            h->hitted = true;
            return;
        }
        step->next_x += step->x_step;
        step->next_y += step->y_step;
    }
}

t_ray_step init_horizontal_ray_step(float x_intercept, float y_intercept,
                                     float x_step, float y_step)
{
    t_ray_step step;

    step.next_x = x_intercept;
    step.next_y = y_intercept;
    step.x_step = x_step;
    step.y_step = y_step;

    return step;
}

/*
If facing South, you want the gridline below you → add tile_size.
If facing North, you want the gridline above you, but if you're exactly on a gridline,
 subtract a tiny amount to avoid peeking into the wrong tile, seeing trhough walls.
 facing south floor(120.5 / 64) = floor(1.8828) = 1
1 * 64 = 64
64 + 64 = 128
facing north floor(120.5 / 64) = 1
1 * 64 = 64
64 + 64 = 128
  // Calc  x at the intercept
tan(angle) = opposite / adjacent = (Δy) / (Δx)
*/

void find_horizontal_collision(t_map *map, t_player *player, float angle, t_cast *h)
{
    float y_intercept;
    float x_intercept;
    float y_step;
    float x_step;

   bool facing_N   = is_ray_facing(NORTH, angle);
   bool facing_S   = is_ray_facing(SOUTH, angle);

    if (facing_N)
        y_intercept = floor(player->y / map->tile_size) * map->tile_size - 0.0001f;
    else 
        y_intercept = floor(player->y / map->tile_size) * map->tile_size + map->tile_size;
       
    x_intercept = player->x + (y_intercept - player->y) / tan(angle);

    if (facing_S)
        y_step = map->tile_size;
    else
        y_step = -map->tile_size;

    x_step = y_step / tan(angle);

    t_ray_step step = init_horizontal_ray_step(x_intercept, y_intercept,
                                     x_step, y_step);
    step.facing_north = facing_N;

   trace_horizontal_ray(map, &step, h);
  
}
