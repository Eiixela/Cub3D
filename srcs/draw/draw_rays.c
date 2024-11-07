/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:38:30 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/07 13:28:29 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static double	calculate_wall_distance(t_data *data, t_vector2D player_coor,
	double *angle)
{
	init_ray(data->ray, angle, player_coor);
	calculate_step_and_side_dist(data->ray, player_coor);
	data->ray->wall_dist = dda(data, data->ray);
	return (final_distance(data->ray, player_coor));
}

static double	draw_one_ray(t_data *data, t_vector2D player_coor,
	double *angle)
{
	return (calculate_wall_distance(data, player_coor, angle));
}

static void    draw_wall_texture(t_data *data, t_draw_params *params,
    int wall_direction)
{
    t_texture    *tex;

    tex = data->tex + wall_direction;
    draw_texture(data, params, tex);
}

static void    draw_wall(t_data *data, double ray_distance, int n_ray,
    double angle)
{
    t_draw_params    params;
    double            perpen_dst;

    perpen_dst = ray_distance * cos(angle - data->map->player_position->angle);
    params.wall_height = (1 / perpen_dst) * data->pplane->dst_from_player;
    params.draw_start = (-((int)params.wall_height >> 1) + (HEIGHT >> 1));
    params.draw_end = (((int)params.wall_height >> 1) + (HEIGHT >> 1));
    params.n_ray = n_ray;
    params.ray_distance = ray_distance;
    if (params.draw_start < 0)
        params.draw_start = 0;
    if (params.draw_end >= HEIGHT)
        params.draw_end = HEIGHT - 1;
    draw_wall_texture(data, &params, data->ray->wall_direction);
}

void	draw_all_rays(t_data *data, t_map *map)
{
	t_vector2D	player_coor;
	double		ray_len;
	int			i;
	double		angle;
	double		angle_step;

	ray_len = 0;
	i = 0;
	player_coor.x = map->player_position->x;
	player_coor.y = map->player_position->y;
	angle = map->player_position->angle - (FOV * 0.5);
	angle_step = FOV / WIDTH;
	while (i < WIDTH)
	{
		ray_len = draw_one_ray(data, player_coor, &angle);
		draw_wall(data, ray_len, i++, angle);
		angle += angle_step;
	}
}
