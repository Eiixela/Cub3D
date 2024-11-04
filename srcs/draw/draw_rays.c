/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:38:30 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/04 13:18:06 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static double	draw_one_ray(t_data *data, t_vector2D player_coor,
	double *angle)
{
	return (calculate_wall_distance(data, player_coor, angle));
}

static void	draw_wall(t_data *data, double ray_distance, int n_ray,
	double angle)
{
	double	perpendicular_distance;
	double	wall_height;
	int		draw_start;
	int		draw_end;

	perpendicular_distance = ray_distance * cos(angle - data->map->player_position->angle);
	wall_height = (1 / perpendicular_distance) * data->pplane->distance_from_player;
	draw_start = (-((int)wall_height >> 1) + (HEIGHT >> 1));
	draw_end = (((int)wall_height >> 1) + (HEIGHT >> 1));
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (data->ray->wall_direction == NORTH)
		draw_texture(data, n_ray, draw_start, draw_end, wall_height, data->tex + NORTH, ray_distance); // UNCOMMENT ME FOR A WILD RIDE
	else if (data->ray->wall_direction == SOUTH)
		draw_texture(data, n_ray, draw_start, draw_end, wall_height, data->tex + SOUTH, ray_distance); // UNCOMMENT ME FOR A WILD RIDE
	else if (data->ray->wall_direction == EAST)
		draw_texture(data, n_ray, draw_start, draw_end, wall_height, data->tex + EAST, ray_distance); // UNCOMMENT ME FOR A WILD RIDE
	else if (data->ray->wall_direction == WEST)
		draw_texture(data, n_ray, draw_start, draw_end, wall_height, data->tex + WEST, ray_distance); // UNCOMMENT ME FOR A WILD RIDE
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
