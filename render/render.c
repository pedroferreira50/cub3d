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
                                          &app->mlx.bpp, &app->mlx.line_length, &app->mlx.endian);
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

void render_frame(t_cub_elements *app)
{
    int x;

    x = 0;
    while (x < app->mlx.width)
    {
        // TODO: cast a ray for column x,
        //       compute wall slice height & texture offset,
        //       sample texture, and write pixels into app->mlx.img_data.
        x++;
    }
    mlx_put_image_to_window(app->mlx.mlx_ptr,
                            app->mlx.win_ptr,
                            app->mlx.img_ptr,
                            0, 0);
}