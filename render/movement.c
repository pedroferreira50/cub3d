/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:10:43 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/12 11:33:06 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player_fwd_bkwd(t_map *map, t_player *player, float speed,
		int direction)
{
	float	move_x;
	float	move_y;

	move_x = cos(player->angle) * speed * direction;
	move_y = sin(player->angle) * speed * direction;
	if (!is_wall(map, player->player_x + move_x + get_padding(move_x),
			player->player_y))
		player->player_x += move_x;
	if (!is_wall(map, player->player_x, player->player_y + move_y
			+ get_padding(move_y)))
		player->player_y += move_y;
}

// left  -1)
// right 1
void	move_strafe(t_map *map, t_player *player, float speed, int direction)
{
	float	move_x;
	float	move_y;
	float	padding_x;
	float	padding_y;

	if (direction == -1)
	{
		move_x = -sin(player->angle) * speed;
		move_y = cos(player->angle) * speed;
	}
	else if (direction == 1)
	{
		move_x = sin(player->angle) * speed;
		move_y = -cos(player->angle) * speed;
	}
	else
		return ;
	padding_x = get_padding(move_x);
	padding_y = get_padding(move_y);
	if (!is_wall(map, player->player_x + move_x + padding_x, player->player_y))
		player->player_x += move_x;
	if (!is_wall(map, player->player_x, player->player_y + move_y + padding_y))
		player->player_y += move_y;
}

// angle delta pos is right neg is left
// amount (in radians) by which you want to rotate the player’s facing angle.
void	rotate_player(t_player *player, float angle_delta)
{
	player->angle += angle_delta;
	player->angle = normalize_angle(player->angle);
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
}

// forward 1
// backward -1
// Handles only linear and strafing movement based on WASD keys.
void	move_player_by_keys(t_map *map, t_player *player, t_keys keys)
{
	if (keys.w)
		move_player_fwd_bkwd(map, player, MOVE_SPEED, 1);
	if (keys.s)
		move_player_fwd_bkwd(map, player, MOVE_SPEED, -1);
	if (keys.a)
		move_strafe(map, player, MOVE_SPEED, -1);
	if (keys.d)
		move_strafe(map, player, MOVE_SPEED, 1);
}

// handle_movement: Handles all movement and rotation,
void	handle_movement(t_data *data)
{
	t_player	*player;
	t_map		*map;
	t_keys		keys;

	player = &data->elem->player;
	map = data->elem->map;
	keys = data->keys;
	if (keys.w || keys.s || keys.a || keys.d)
		move_player_by_keys(map, player, keys);
	if (keys.left)
		rotate_player(player, -ROTATE_SPEED);
	if (keys.right)
		rotate_player(player, ROTATE_SPEED);
}
