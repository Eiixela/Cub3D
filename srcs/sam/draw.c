/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:07:23 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/16 19:47:48 by saperrie         ###   ########.fr       */
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
	pixels += (data->width * 2048) + (data->width * 2); // offset to show in center of screen
	y = 0.;
	while (y < height)
	{
		x = 0.;
		while (x < width)
		{
			if (map->map[x][y] == '1')
				((int *)pixels)[(int)x + width * (int)y] = (0xfff5ff);
			else if ((x == 8 && y == 8) || \
			(x == 9 && y == 8) || (x == 8 && y == 9) || \
			(x == 9 && y == 9)) // THIS IS HARD CODED PLAYER COORDINATE IN 2x2
				((int *)pixels)[(int)x + width * (int)y] = (0xf02d00);
			else if (map->map[x][y] == 'F')
				((int *)pixels)[(int)x + width * (int)y] = (0x003eff);
			// else if (!find_player(map->map[x][y]))
			x += 1;
		}
		pixels += (2500 - x) * 4;
		y += 1;
	}
	return (0);
}
