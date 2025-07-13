#include "cub3d_parsing.h"

// Calc how far to step for each next horizontal gridline intersection
float	calculate_y_intercept(t_player *player, t_map *map, float angle)
{
	int	tile_y;

	tile_y = floor(player->y / map->tile_size) * map->tile_size;
	if (is_facing_north(angle))
		return (tile_y - 0.0001f);
	else
		return (tile_y + map->tile_size);
}

static void	trace_horizontal_ray(t_map *map, t_ray_step *step, t_cast *h)
{
	int	map_x;
	int	map_y;

	while (1)
	{
		map_x = (int)(step->next_x) / map->tile_size;
		if (step->vertical_dir == NORTH)
			map_y = ((int)(step->next_y) - 1) / map->tile_size;
		else
			map_y = (int)(step->next_y) / map->tile_size;
		if (map_x < 0 || map_x >= map->width || map_y < 0
			|| map_y >= map->height)
		{
			h->hitted = false;
			return ;
		}
		if (map->map[map_y][map_x] == '1')
		{
			h->hit[X] = step->next_x;
			h->hit[Y] = step->next_y;
			h->hitted = true;
			return ;
		}
		step->next_x += step->x_step;
		step->next_y += step->y_step;
	}
}

t_ray_step	init_horizontal_ray_step(float x_intercept, float y_intercept,
		float x_step, float y_step)
{
	t_ray_step	step;

	step.next_x = x_intercept;
	step.next_y = y_intercept;
	step.x_step = x_step;
	step.y_step = y_step;
	return (step);
}

/*
If facing South, you want the gridline below you → add tile_size.
If facing North, you want the gridline above you,
	but if you're exactly on a gridline,
 subtract a tiny amount to avoid peeking into the wrong tile,
	seeing trhough walls.
 facing south floor(120.5 / 64) = floor(1.8828) = 1
1 * 64 = 64
64 + 64 = 128
facing north	floor(120.5 / 64) = 1
1 * 64 = 64
64 + 64 = 128
  // Calc  x at the intercept
tan(angle) = opposite / adjacent = (Δy) / (Δx)
*/

void	find_horizontal_collision(t_map *map, t_player *player, float angle,
		t_cast *h)
{
	float		y_i;
	float		x_i;
	float		y_step;
	float		x_step;
	t_ray_step	step;
	t_direction	vertical_dir;

	if (is_ray_facing(NORTH, angle))
		vertical_dir = NORTH;
	else
		vertical_dir = SOUTH;
	if ((vertical_dir == NORTH))
		y_i = floor(player->y / map->tile_size) * map->tile_size - 0.0001f;
	else
		y_i = floor(player->y / map->tile_size) * map->tile_size
			+ map->tile_size;
	x_i = player->x + (y_i - player->y) / tan(angle);
	if (vertical_dir == SOUTH)
		y_step = map->tile_size;
	else
		y_step = -map->tile_size;
	x_step = y_step / tan(angle);
	step = init_horizontal_ray_step(x_i, y_i, x_step, y_step);
	step.vertical_dir = vertical_dir;
	trace_horizontal_ray(map, &step, h);
}
