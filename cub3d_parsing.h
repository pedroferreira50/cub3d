#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

//# include "libft/libft.h"
# include <fcntl.h>
#include <math.h>
#include <limits.h>
# include <unistd.h>
# include <stdbool.h>

#define PI         3.14159265
#define TWO_PI     6.28318530
#define HALF_PI    1.57079632

typedef enum e_direction
{
  EAST,
	NORTH,
	WEST,
	SOUTH,
}	t_direction;
typedef struct s_cub_elements
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
  int               screen_width; //just realised i need this sorry 
  int               screen_height;
  t_map map;
  t_texture texture;
  t_mlx mlx;
  t_player *player; 
	int		floor_color[3];// could we make a sep colour struct for these? and put a ptr to it in here?? 
	int		ceiling_color[3]; // could we make a sep colour struct for these? and put a ptr to it in here?? 
	char	**map;
	bool	ceiling_color_set; // could we make a sep colour struct for these? and put a ptr to it in here?? 
	bool	floor_color_set; // could we make a sep colour struct for these? and put a ptr to it in here?? 
}	t_cub_elements;


typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture {
    char    *path;       // file path to the .xpm (or .png) file
    void    *data;       // MLX image pointer returned by mlx_xpm_file_to_image
    int     width;       // texture width in pixels
    int     height;      // texture height in pixels
}   t_texture;


typedef struct s_cast {
    bool    hitted;         // did this ray hit?
    float   hit[2];         // exact X,Y hit point
    float   distance;       // perp-corrected distance
    char    content;        // map cell content ('1' for wall)
}   t_cast;

typedef struct s_ray {
    float   dist;           // distance from player
    float   angle;          // ray angle
    int     hit[2];         // grid cell hit (x,y)
    bool    up;             // facing up?
    bool    left;           // facing left?
    bool    vertical_hit;   // did we hit a vertical wall?
    char    wall_content;   // which wall texture to use ('N','S','E','W')
}   t_ray;

typedef struct s_texture
{
	char	*path;
	void	*data;
	int		width;
	int		height;
}	t_texture;


typedef struct s_color
{
	int		rgb_color[3]; // [0]=R, [1]=G, [2]=B
	bool	color_set;   // whether this color was parsed
	int		hex_color;  // optional convenience: combine rgb into 0xRRGGBB
}	t_color;


typedef struct s_player {
    float   x;           // player pos X
    float   y;           // player pos Y
    float   dir_x;       // direction vector X
    float   dir_y;       // direction vector Y
    float   plane_x;     // camera plane X
    float   plane_y;     // camera plane Y
    float   angle;       // current facing angle (optional)
    float   ray_step;    // horizontal FOV step per column
}   t_player;

typedef struct s_mlx {
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;      // screen width
    int     height;     // screen height
}   t_mlx


void	check_arguments(int argc, char **argv);
int		ft_strcmp(const char *s1, const char *s2);
bool	scan_cub_elements(const char *filename, t_cub_elements *cub3d);
bool	assign_color(char *id, char *val, t_cub_elements *cub3d);
bool	is_map_line(char *line);
bool	close_and_free(char *line, int fd, t_cub_elements *cub3d, bool retu);
void	free_cub_elements(t_cub_elements *cub3d);
char	*trim_spaces(char *str);
bool	map_parsing(const char *filename, t_cub_elements *cub3d);
t_map	*init_map(void);
void	free_map(t_map *map);
void	free_texture(t_texture *texture);

//RENDERER
void render_frame(t_cub_elements *app);
void init_renderer(t_cub_elements *app, int screen_w, int screen_h);
void destroy_renderer(t_cub_elements *app);


#endif