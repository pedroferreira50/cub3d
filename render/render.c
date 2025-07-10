#include "../cub3d_parsing.h"

// app var means it holds everything i need at run time
void init_renderer(t_cub_elements *app, int screen_w, int screen_h)
{
    
    app->mlx.mlx_ptr = mlx_init();
    app->mlx.win_ptr = mlx_new_window(app->mlx.mlx_ptr,
                                      screen_w, screen_h,
                                      "cub3d");
    app->mlx.img_ptr = mlx_new_image(app->mlx.mlx_ptr,
                                     screen_w, screen_h);
    app->mlx.img_data = mlx_get_data_addr(app->mlx.img_ptr,
                                          &app->mlx.bits_per_pixel, &app->mlx.line_length, &app->mlx.endian);
    app->mlx.width = screen_w;
    app->mlx.height = screen_h;
}

void destroy_renderer(t_cub_elements *app)
{
    if (app->mlx.img_ptr)
        mlx_destroy_image(app->mlx.mlx_ptr, app->mlx.img_ptr);
    if (app->mlx.win_ptr)
        mlx_destroy_window(app->mlx.mlx_ptr, app->mlx.win_ptr);
}

/*
Casts a ray per vertical stripe x.
Performs DDA to find the first wall hit.
Calculates perpendicular distance to correct fish‑eye.
Computes line height for that slice.
Selects the correct wall texture based on hit side.
Samples the texture per screen pixel y in the slice.
*/
/* High‑level routine you call each frame */
void render_frame(t_cub_elements  *app)
{
    static t_ray *rays = NULL;
    if (!rays)
        rays = malloc(sizeof(*rays) * app->screen_width);

    raycasting(app, rays);
    draw_walls(app, rays);
}