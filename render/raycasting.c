#include "cub3d_parsing.h"

/* Copies data from prev col if two distances tie ie same distanc */
static void copy_last_ray(t_ray *rays, int col)
{
    t_ray *curr = &rays[col];
    t_ray *prev = &rays[col - 1];
    *curr = *prev;  // struct copy: angle, dist, hit[], wall_content, flags...
}

/* Stores whichever of `h` or `v` was closer into the ray array */
static void cast_ray(t_cub_elements  *app, float angle, int col, t_ray *rays)
{
    t_cast h, v;
    find_horizontal_collision(&app->config, &app->player, angle, &h);
    find_vertical_collision  (&app->config, &app->player, angle, &v);

    /* Correct for fish-eye distortion */
    float fish_eye = cos(app->player.angle - angle);
    if (!h.hitted) h.distance = INFINITY;
    else           h.distance = hit_distance(app->player.x, app->player.y, h.hit[X], h.hit[Y]) * fish_eye;
    if (!v.hitted) v.distance = INFINITY;
    else           v.distance = hit_distance(app->player.x, app->player.y, v.hit[X], v.hit[Y]) * fish_eye;

    if (h.distance < v.distance)
    {
        store_ray_data(&rays[col], &h, angle, /*vertical_hit=*/FALSE);
    }
    else if (v.distance < h.distance)
    {
        store_ray_data(&rays[col], &v, angle, /*vertical_hit=*/TRUE);
    }
    else if (col > 0)
    {
        copy_last_ray(rays, col);
    }
}

/* Cast a ray for each column across the screen */
void raycasting(t_cub_elements  *app, t_ray *rays)
{
    float angle = app->player.angle - HALF_FOV;
    for (int col = 0; col < app->screen_width; col++, angle += app->player.ray_step)
    {
        angle = normalize_angle(angle);
        cast_ray(app, angle, col, rays);
    }
}

/* Draws vertical wall slices based on distances in `rays[]` */
void draw_walls(t_cub_elements  *app, t_ray *rays)
{
    for (int x = 0; x < app->screen_width; x++)
    {
        t_ray *ray = &rays[x];
        int line_h = (int)(app->screen_height / ray->dist);
        int start = MAX(0, -line_h/2 + app->screen_height/2);
        int end   = MIN(app->screen_height-1, line_h/2 + app->screen_height/2);

        /* pick texture by ray->wall_content or ray->vertical_hit */
        t_texture *tex = &app->textures[ray->wall_content];
        double wallX   = (ray->vertical_hit)
                       ? (app->player.y + ray->dist * ray->dir_y)
                       : (app->player.x + ray->dist * ray->dir_x);
        wallX = wallX - floor(wallX);
        int texX = (int)(wallX * tex->width);
        if (ray->vertical_hit && ray->dir_x > 0)      texX = tex->width - texX - 1;
        if (!ray->vertical_hit && ray->dir_y < 0)     texX = tex->width - texX - 1;

        double step = (double)tex->height / line_h;
        double texPos = (start - app->screen_height/2 + line_h/2) * step;

        for (int y = start; y < end; y++, texPos += step)
        {
            int texY  = (int)texPos & (tex->height - 1);
            int color = get_tex_pixel(tex, texX, texY);
            put_pixel(app->mlx.img_data, x, y, color, &app->mlx);
        }
    }
    mlx_put_image_to_window(app->mlx.mlx_ptr,
                           app->mlx.win_ptr,
                           app->mlx.img_ptr,
                           0, 0);
}



void store_ray_data(t_ray *ray, t_cast *cast, float angle, bool vertical)
{
    ray->angle = angle;
    ray->dist = cast->distance;
    ray->hit[X] = cast->hit[X];
    ray->hit[Y] = cast->hit[Y];
    ray->wall_content = cast->content;
    ray->vertical_hit = vertical;
}