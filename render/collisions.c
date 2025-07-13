#include "cub3d_parsing.h"

void find_horizontal_collision(t_map *map, t_player *player, float angle, t_cast *h)
{
    float y_intercept;
    float x_intercept;
    float y_step;
    float x_step;

   bool facing_up   = is_ray_facing(NORTH, angle);
  
    if (facing_up)
        y_intercept = floor(player->y / map->tile_size) * map->tile_size - 0.0001f;
    else 
        y_intercept = floor(player->y / map->tile_size) * map->tile_size + map->tile_size;
       
    // Calculate corresponding x at the intercept
    x_intercept = player->x + (y_intercept - player->y) / tan(angle);

    bool facing_down   = is_ray_facing(SOUTH, angle);
  
    // Calculate how far to step for each next horizontal gridline intersection
    y_step = facing_down ? map->tile_size : -map->tile_size;
    x_step = y_step / tan(angle);

    // Initialize next intersection
    float next_x = x_intercept;
    float next_y = y_intercept;

    while (true)
    {
        // Map grid indices (convert from world coords to grid coords)
        int map_x = (int)(next_x) / map->tile_size;
        int map_y = (int)(next_y + (facing_up ? -1 : 0)) / map->tile_size;
        // The `(facing_up ? -1 : 0)` adjusts the tile checking because
        // when facing up, ray hits just below the horizontal line, so check tile above.

        // Check bounds
        if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
        {
            h->hitted = false;
            break;
        }

        // Check if map tile is a wall
        if (map->map[map_y][map_x] == '1')
        {
            h->hit[X] = next_x;
            h->hit[Y] = next_y;
            h->hitted = true;
            break;
        }
        else
        {
            // Move to next horizontal grid intersection
            next_x += x_step;
            next_y += y_step;
        }
    }
}