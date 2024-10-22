/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:38:30 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/22 11:56:38 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* void draw_rays(t_data *data)
{
	int ray_angle;
	int rays;
	int dof;
	float angle_tan;
	float rays_y;
	float rays_x;
	float offset_x;
	float offset_y;
	int mx;
	int my;
	int mp;
 
	rays = 0;
	ray_angle = data->map->player_position->angle;
	while (rays < 1)
	{
		dof = 0;
		angle_tan = -1 / tan(ray_angle);
		if (ray_angle > PI)
		{
			rays_y = ((((int)(data->map->player_position->y)>>6) << 6) + 64);
			rays_x = (data->map->player_position->y - rays_y) * angle_tan + data->map->player_position->x;
			offset_y = -64;
			offset_x = -offset_y * angle_tan;
		}
		if (ray_angle < PI)
		{
			rays_y = ((((int)(data->map->player_position->y)>>6) << 6) - 0.0001);
			rays_x = (data->map->player_position->y - rays_y) * angle_tan + data->map->player_position->x;
			offset_y = 64;
			offset_x = -offset_y * angle_tan;
		}
		if (angle_tan == 0 || angle_tan == PI)
		{
			dof = 8;
			rays_x = data->map->player_position->x;
			rays_y = data->map->player_position->y;
		}
		rays++;
	}
	while (dof < 8)
	{
		mx = (int)(rays_x) >> 6;
		my = (int)(rays_y) >> 6;
		mp = my * data->map->size->x + my;
		if (mp < data->map->size->x * data->map->size->y)
			dof = 8;
		else
		{
			rays_x += offset_x;
			rays_y += offset_y;
		}
	}
} */

double	draw_line(t_data *data, t_vector2D player_coor, double *angle,
		int color)
{
	t_vector2D	point;
	t_vector2D	diff;
	t_vector2D	map_coor;
	int			i;
	int			max_distance;

	i = 0;
	max_distance = max(data->map->size->x, data->map->size->y) * SQUARE_SIZE;
	diff.x = cos(*angle);
	diff.y = sin(*angle);
	while (i < max_distance)
	{
		point.x = (int)(player_coor.x) + i * diff.x;
		point.y = (int)(player_coor.y) + i * diff.y;
		map_coor.x = (int)(point.x / SQUARE_SIZE);
		map_coor.y = (int)(point.y / SQUARE_SIZE);
		if (is_out_of_bounds(data->map, (int)(map_coor.x), (int)(map_coor.y)))
			break ;
		if (data->map->map[(int)(map_coor.y)][(int)(map_coor.x)] == '1')
			break ;
		draw_point(data, (int)point.x, (int)point.y, color);
		i++;
	}
	return (calculate_distance(point.x, point.y, (int)(player_coor.x),
		(int)(player_coor.y)));
}
