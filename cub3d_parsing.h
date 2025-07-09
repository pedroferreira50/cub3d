#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

//will assign 0 1 2 3 automatically
typedef enum e_wall {
  NORTH,
  SOUTH,
  EAST,
  WEST
} t_wall;

//might need math constants 
#define PI      3.14159265f
#define TWO_PI  6.28318530f

//keys
#define ESC    0xff1b
#define UP     0xff52
#define DOWN   0xff54
#define LEFT   0xff51
#define RIGHT  0xff53

#define X   0
#define Y   1
#define COL 0
#define ROW 1

//core game constants 
#define TILE_SIZE     64
#define HALF_TILE     32    // used when centering textures
#define PLAYER_HEIGHT 32
#define SCALE         0.12f // minimap or UI scale factor
#define FOV           1.047198f   // 60° in radians
#define HALF_FOV      0.523599f   // 30° in radians

/* typedef struct s_elements {
    bool	no;
    bool	so;
    bool	we;
    bool	ea;
    bool	f;
    bool	c;
}	t_elements; */

typedef struct s_cub_elements
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];// could we make a sep colour struct for these? and put a ptr to it in here?? 
	int		ceiling_color[3]; // could we make a sep colour struct for these? and put a ptr to it in here?? 
	char	**map;
	bool	ceiling_color_set; // could we make a sep colour struct for these? and put a ptr to it in here?? 
	bool	floor_color_set; // could we make a sep colour struct for these? and put a ptr to it in here?? 
}	t_cub_elements;

// 


// 2D array of chars 
typedef struct s_map
{
    char    **map;       // i think this is thesame asyourone?maybe it isbetter to keep it in the central cub3d struct?? or we could have a pointer tothe map struct??
    int     width; //COULDCALL THIS ROWS
    int     height; // COULD CALL THIS COLUMNS IF LESS CONFUSING?? 
}   t_map;

typedef struct s_texture {
    char    *img_path;
    void    *data; //img obj loaded by minilibx eg use its fntcs to file to image so the image becomes useable data
    int     width;
    int     height;
} t_texture;

//ALl MLX-related pointers and info (window, image, etc): ie anything from mlx lib
typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}   t_mlx;

  // Camera plane for 3D projection

typedef struct s_player {
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_player;

// TO DO RAYCASTING STRUCT DO NOT KNOW ENOUGH ABOUT IT 

void	check_arguments(int argc, char **argv);
int		ft_strcmp(const char *s1, const char *s2);
bool	scan_cub_elements(const char *filename, t_cub_elements *cub3d);
bool	assign_color(char *id, char *val, t_cub_elements *cub3d);
bool	is_map_line(char *line);
bool	close_and_free(char *line, int fd, t_cub_elements *cub3d, bool retu);
void	free_cub_elements(t_cub_elements *cub3d);
char	*trim_spaces(char *str);
bool	map_parsing(const char *filename, t_cub_elements *cub3d);

#endif