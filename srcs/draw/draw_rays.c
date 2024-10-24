/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:38:30 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/24 18:01:19 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static double	calculate_final_distance(t_ray_data *ray, t_vector2D player_coor)
{
	double	wall_dist;

	if (ray->side == 0)
		wall_dist = (ray->map_pos.x - player_coor.x / SQUARE_SIZE
				+ (1 - ray->step.x) / 2) / ray->ray_dir.x;
	else
		wall_dist = (ray->map_pos.y - player_coor.y / SQUARE_SIZE
				+ (1 - ray->step.y) / 2) / ray->ray_dir.y;
	return (wall_dist * SQUARE_SIZE);
}

static double	perform_dda(t_data *data, t_ray_data *ray)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->side = 1;
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
		ray->side_dist.x = (player_coor.x / SQUARE_SIZE - ray->map_pos.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - player_coor.x / SQUARE_SIZE)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player_coor.y / SQUARE_SIZE - ray->map_pos.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - player_coor.y / SQUARE_SIZE)
			* ray->delta_dist.y;
	}
}

static void	initialize_ray_variables(t_ray_data *ray, double *angle,
	t_vector2D player_coor)
{
	ray->ray_dir.x = cos(*angle);
	ray->ray_dir.y = sin(*angle);
	ray->map_pos.x = (int)(player_coor.x / SQUARE_SIZE);
	ray->map_pos.y = (int)(player_coor.y / SQUARE_SIZE);
	ray->delta_dist.x = fabs(SQUARE_SIZE / ray->ray_dir.x);
	ray->delta_dist.y = fabs(SQUARE_SIZE / ray->ray_dir.y);
}

static double	calculate_wall_distance(t_data *data, t_vector2D player_coor,
	double *angle)
{
	t_ray_data	ray;

	initialize_ray_variables(&ray, angle, player_coor);
	calculate_step_and_side_dist(&ray, player_coor);
	ray.wall_dist = perform_dda(data, &ray);
	return (calculate_final_distance(&ray, player_coor));
}

static double	draw_one_ray(t_data *data, t_vector2D player_coor,
	double *angle)
{
	return (calculate_wall_distance(data, player_coor, angle));
}

void	draw_wall(t_data *data, double ray_distance, int n_ray,
	double angle)
{
	double perpendicular_distance;
	double wall_height;
	int draw_start;
	int draw_end;

	perpendicular_distance = ray_distance * cos(angle - \
			data->map->player_position->angle);
	wall_height = (HEIGHT / perpendicular_distance) * SQUARE_SIZE;
	draw_start = (int)(-(wall_height / 2) + (HEIGHT / 2));
	draw_end = (int)((wall_height / 2) + (HEIGHT / 2));
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	while (draw_start <= draw_end)
		draw_point(data, n_ray, draw_start++, LIME_GREEN);
}

void	draw_all_rays(t_data *data, t_map *map)
{
	t_vector2D	player_coor;
	double		ray_len;
	int			i;
	int			j;
	double		angle;

	ray_len = 0;
	i = 0;
	j = 0;
	player_coor.x = map->player_position->x * SQUARE_SIZE;
	player_coor.y = map->player_position->y * SQUARE_SIZE;
	angle = map->player_position->angle - FOV / 2;
	while (i++ < WIDTH)
	{
		ray_len = draw_one_ray(data, player_coor, &angle);
		draw_wall(data, ray_len, i, angle);
		angle += FOV / WIDTH;
	}
}
