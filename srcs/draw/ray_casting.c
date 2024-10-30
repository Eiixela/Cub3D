/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:11:48 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/30 16:41:01 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static double	final_distance(t_ray_data *ray, t_vector2D player_coor)
{
	double	wall_dist;

	if (ray->side == 0)
		wall_dist = (ray->map_pos.x - player_coor.x
				+ (1 - ray->step.x) / 2) / ray->ray_dir.x;
	else
		wall_dist = (ray->map_pos.y - player_coor.y
				+ (1 - ray->step.y) / 2) / ray->ray_dir.y;
	return (wall_dist);
}

static double	dda(t_data *data, t_ray_data *ray)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->side = 0;
			data->tex->side = 0;
			if (ray->step.x > 0)
				ray->wall_direction = EAST;
			else
				ray->wall_direction = WEST;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->side = 1;
			data->tex->side = 1;
			if (ray->step.y > 0)
				ray->wall_direction = SOUTH;
			else
				ray->wall_direction = NORTH;
		}
		if (is_out_of_bounds(data->map, (int)ray->map_pos.x,
				(int)ray->map_pos.y))
			break ;
		if (data->map->map[(int)ray->map_pos.y][(int)ray->map_pos.x] == '1')
			break ;
	}
	return (0);
}

static void	calculate_step_and_side_dist(t_ray_data *ray,
	t_vector2D player_coor)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player_coor.x - ray->map_pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - player_coor.x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player_coor.y - ray->map_pos.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - player_coor.y)
			* ray->delta_dist.y;
	}
}

static void	init_ray(t_ray_data *ray, double *angle,
	t_vector2D player_coor)
{
	ray->ray_dir.x = cos(*angle);
	ray->ray_dir.y = sin(*angle);
	ray->map_pos.x = (int)(player_coor.x );
	ray->map_pos.y = (int)(player_coor.y );
	ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	ray->wall_direction = 0;
}

double	calculate_wall_distance(t_data *data, t_vector2D player_coor,
	double *angle)
{
	t_ray_data	ray;

	data->ray = &ray;
	init_ray(&ray, angle, player_coor);
	calculate_step_and_side_dist(&ray, player_coor);
	ray.wall_dist = dda(data, &ray);
	return (final_distance(&ray, player_coor));
}
