/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:26:20 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/27 18:16:55 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <unistd.h>

// maths defines
# define M_PI 3.14159265358979323846
# define PI 3.14159265
# define TWO_PI 6.28318530
# define HALF_PI 1.57079632

# define FOV 1.0471975512      // 60 degrees in radians (M_PI / 3)
# define HALF_FOV 0.5235987756 // (FOV / 2)

# define MOVE_SPEED 1.0f    // Speed of forward/backward/strafe
# define ROTATE_SPEED 0.05f // Radians per frame (~3 degrees)

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

//# define KEYPRESS 2
//# define KeyRelease 3
//# define DestroyNotify 17
//# define KeyPressMask (1L << 0)
//# define KeyReleaseMask (1L << 1)
//# define NoEventMask 0

# define COLLISION_PADDING 5.0

# define WIDTH 640
// we are defining a viewport to play the game so it ok to hardcode this
# define HEIGHT 480

# define TILE_SIZE 64

typedef struct s_map
{
	char			**map;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	int				tile_size;
}					t_map;

typedef struct s_texture
{
	void			*img_ptr;
	char			*data;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			*path;
}					t_texture;
// mlx image pointer *img_ptr;
// pixel buffer (same as data_addr) char *data;
// optional, for debug or filepathchar *path;
typedef struct s_color
{
	int				rgb_color[3];
	bool			color_set;
	int				hex_color;
}					t_color;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_data;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	int				color;
}					t_mlx;
// screen w int width;
// screen h  int height;
// column color 	int color;
typedef struct s_keys
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
}					t_keys;

typedef struct s_player
{
	float			player_x;
	float			player_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			angle;
	float			ray_step;
}					t_player;
// dir vect X 	float dir_x;
// dir vec Y 	float dir_y;
// cam plane X 	float plane_x;
// cam plane Y 	float plane_y;
// curr facing angle 	float angle;
// horizontal FOV step per column float ray_step;
typedef struct s_cub_elements
{
	t_texture		*no_text;
	t_texture		*so_text;
	t_texture		*we_text;
	t_texture		*ea_text;
	t_color			*floor_color;
	t_color			*ceiling_color;
	t_map			*map;
	char			**cub_file;
	t_player		player;
	t_texture		texture;
}					t_cub_elements;

typedef struct s_ray
{
	float			distance;
	float			correct_dist;
	float			angle;
	double			hit[2];
	bool			vertical_hit;
	char			wall_content;
}					t_ray;
// distance corrected for fish-eye 	float correct_dist;
// ray angle float angle;
// exact hit coords 	double hit[2];
// did we hit a vertical wall? 	bool vertical_hit; /
// which wall texture to use ('N','S','E','W') //	char wall_content;
// pixel y for top of wall int wall_top;
// pixel y for bottom of wall 	int wall_bottom;
typedef struct s_data
{
	t_mlx			*mlx;
	t_cub_elements	*elem;
	t_keys			keys;
	int				closing;
	t_ray			*rays;
	int				rays_w;
}					t_data;
// store width for realloc DO I REALLLY NEED THIS ?? int rays_w;
typedef enum e_direction
{
	EAST,
	NORTH,
	WEST,
	SOUTH
}					t_direction;

enum
{
	X,
	Y
};

typedef struct s_cast
{
	bool			hitted;
	float			hit[2];
	float			distance;
	char			content;
}					t_cast;
// exact X,Y hit point 	float hit[2];
// perp-corrected distance float distance;
// map cell content ('1' for wall) 	char content;
typedef struct s_ray_step
{
	float			next_x;
	float			next_y;
	float			x_step;
	float			y_step;
	t_direction		vertical_dir;
	t_direction		horizontal_dir;
}					t_ray_step;

typedef struct s_render_slice
{
	int				x;
	int				texx;
	int				start;
	int				end;
	int				line_h;
	double			line_h_d;
}					t_render_slice;
// clamped integer height (for drawing) 	int line_h;
// original projected height (double) — for texture mapping   double line_h_d;
typedef struct s_slice
{
	int				top_pixel;
	int				bottom_pixel;
	int				height;
}					t_slice;

void				check_arguments(int argc, char **argv, t_data *data);
int					ft_strcmp(const char *s1, const char *s2);
bool				scan_cub_elements(char *filename, t_cub_elements *cub3d,
						t_color *ceil, t_color *floor);
bool				assign_color(char *id, char *val, t_cub_elements *cub3d);
bool				is_map_line(char *line);
bool				close_and_free(char *line, int fd, t_cub_elements *cub3d,
						bool retu);
void				free_cub_elements(t_cub_elements *cub3d, void *mlx_ptr);
char				*trim_spaces(char *str);
bool				map_parsing(t_cub_elements *cub3d);
t_map				*init_map(void);
char				**copy_map(char **map, int height);
void				free_map(t_map *map);
void				free_texture(t_texture *texture, void *mlx_ptr);
int					init_mlx(t_mlx *mlx);
bool				cub3d_parsing(int argc, char **argv, t_data *data);
bool				validate_map(t_cub_elements *cub3d);
int					xpm_to_img(t_cub_elements *elem, t_mlx *mlx);
int					data_init(int argc, char **argv, t_data *data);
void				free_array(char **array);
bool				check_color_id(char *id, t_cub_elements *cub3d);
char				*join_strings(char **strings);
bool				elements_loaded(t_cub_elements *cub3d,
						t_color *ceil, t_color *floor);
char				**store_cub(const char *filename);
bool				normalise_map_lines(t_map *map);

// render
// render.c
int					handle_keyrelease(int keycode, t_data *data);
int					handle_keypress(int keycode, t_data *data);
void				render_frame(t_data *app);
void				move_player(t_map *map, t_player *player, t_keys keys);
void				handle_movement(t_data *data);

// putline.c
void				fill_floor(t_mlx *mlx, t_cub_elements *elem, int x,
						int start);
void				fill_ceiling(t_mlx *mlx, t_cub_elements *elem, int x,
						int start);
void				put_pixel(int x, int y, int color, t_mlx *mlx);
// void fill_column(t_mlx *mlx, int x, int y_start, int y_end, int color);
// int rgb_to_hex(int rgb[3]);
t_texture			*select_texture(t_cub_elements *app, t_ray *ray);

// collisions_hor.c
void				find_horizontal_collision(t_map *map, float angle,
						t_cast *h, t_player *player);
t_ray_step			init_ray_step(float x_intercept, float y_intercept,
						float x_step, float y_step);
float				calculate_intercept(float angle, t_player *player,
						bool is_vertical);
void				find_vertical_collision(t_map *map, float angle, t_cast *v,
						t_player *player);
int					get_map_y(t_ray_step *step);

// draw_walls.c
void				draw_walls(t_mlx *mlx, t_ray *rays, t_cub_elements *elem);

// raycasting.c
void				raycasting(t_data *app, t_ray *rays, t_cub_elements *elem);

// raycasting utils
bool				is_ray_facing(int dir, float angle);
t_ray_step			init_horizontal_step(t_player *player, float angle);
t_ray_step			init_vertical_step(t_player *player, float angle);

// utils.c
float				hit_distance(float x1, float y1, float x2, float y2);
float				normalize_angle(float angle);
t_ray_step			init_ray_step(float x_intercept, float y_intercept,
						float x_step, float y_step);
float				get_padding(float move);
bool				is_wall(t_map *map, float x, float y);

int					get_tex_pixel(t_texture *tex, int x, int y);

int					handle_close(t_data *data);
void				free_all_safe(t_data *data);

// movement.c
bool				is_wall(t_map *map, float x, float y);
void				move_forward(t_map *map, t_player *player, float speed);
void				move_backward(t_map *map, t_player *player, float speed);
void				move_left(t_map *map, t_player *player, float speed);
void				rotate_left(t_player *player, float angle);
void				rotate_right(t_player *player, float angle);
void				move_right(t_map *map, t_player *player, float speed);

// free_render.c
void				safe_destroy_image(t_mlx *m, void **img_ptr);
void				clear_image(t_mlx *mlx, int color);
void				safe_destroy_window(t_mlx *m);
void				safe_destroy_display_and_free(t_mlx *m);

// draw_walls_utils.c
double				correct_distance(t_ray *ray, t_player *player);
int					get_line_height(double corrected_dist,
						double dist_proj_plane);

#endif