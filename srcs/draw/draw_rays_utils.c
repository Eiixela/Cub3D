/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:39:12 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/23 14:38:40 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	is_out_of_bounds(t_map *map, int map_x, int map_y)
{
	return (map_x < 0 || map_x >= map->size->y || map_y < 0
		|| map_y >= map->size->x);
}

void	draw_point(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		((int *)data->img.addr)[y * WIDTH + x] = color;
}

double	calculate_distance(double x, double y, double x1, double y1)
{
	return (sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1)));
}
