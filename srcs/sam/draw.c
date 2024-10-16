/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:07:23 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/16 17:47:56 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	draw_2d_map(t_map *map, t_data *data)
{
	char	*pixels;
	int		x;
	int		y;
	int		width;
	int		height;

	width = map->size->x;
	height = map->size->y;
	pixels = data->img.addr;
	y = 0.;
	while (y < height)
	{
		x = 0.;
		while (x < width)
		{
			if (map->map[x][y] == '1')
				((int *)pixels)[(int)x + width * (int)y] = (0xfff5ff);
			else if (map->map[x][y] == 'F')
				((int *)pixels)[(int)x + width * (int)y] = (0xff2d00);
			else if (!find_player(map->map[x][y]))
				((int *)pixels)[(int)x + width * (int)y] = (0x70ff00);

			x += 1;
		}
		pixels += (2500 - x) * 4;
		y += 1;
	}
	return (0);
}
