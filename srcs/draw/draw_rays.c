/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:38:30 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/22 14:16:58 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
