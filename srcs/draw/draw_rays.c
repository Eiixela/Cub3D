/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:38:30 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/07 15:29:06 by aljulien         ###   ########.fr       */
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

static void	draw_wall(t_data *data, double ray_distance, int n_ray,
	double angle)
{
	t_draw_params	draw_param;

	draw_param.n_ray = n_ray;
	draw_param.perpen_dst = ray_distance * cos(angle \
		- data->map->player_position->angle);
	draw_param.wall_height = (1 / draw_param.perpen_dst) \
		* data->pplane->dst_from_player;
	draw_param.draw_start = (-((int)draw_param.wall_height >> 1) \
		+ (HEIGHT >> 1));
	draw_param.draw_end = (((int)draw_param.wall_height >> 1) + (HEIGHT >> 1));
	if (draw_param.draw_start < 0)
		draw_param.draw_start = 0;
	if (draw_param.draw_end >= HEIGHT)
		draw_param.draw_end = HEIGHT - 1;
	if (data->ray->wall_direction == NORTH)
		draw_texture(data, &draw_param, data->tex + NORTH, ray_distance);
	else if (data->ray->wall_direction == SOUTH)
		draw_texture(data, &draw_param, data->tex + SOUTH, ray_distance);
	else if (data->ray->wall_direction == EAST)
		draw_texture(data, &draw_param, data->tex + EAST, ray_distance);
	else if (data->ray->wall_direction == WEST)
		draw_texture(data, &draw_param, data->tex + WEST, ray_distance);
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
