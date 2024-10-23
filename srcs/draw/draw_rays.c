/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:38:30 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/23 12:39:52 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static double	draw_one_ray(t_data *data, t_vector2D player_coor, double *angle,
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

void draw_wall(t_data *data, double ray_distance, int n_ray)
{
	double	wall_height;
	int		draw_start;
	int		draw_end;
	int 	i;

	wall_height = (HEIGHT / ray_distance) * SQUARE_SIZE;
	draw_start = - (wall_height / 2) + (HEIGHT / 2);
	i = draw_start;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (wall_height / 2) + (HEIGHT / 2);
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
    while (i++ <= draw_end)
		draw_point(data, n_ray, i, LIME_GREEN);
}


void	draw_all_rays(t_data *data, t_map *map)
{
	t_vector2D	player_coor;
	double		ray_len;
	int			i;
	int			j;
	double angle;

	ray_len = 0;
	i = 0;
	j = 0;
	player_coor.x = map->player_position->x * SQUARE_SIZE;
	player_coor.y = map->player_position->y * SQUARE_SIZE;
	angle = map->player_position->angle - FOV / 2;
	printf("%f\n", angle);
	while (i++ < WIDTH)
	{
		ray_len = draw_one_ray(data, player_coor, &angle, PINK);
		draw_wall(data, ray_len, i);
		angle += FOV / WIDTH;
	}
}

