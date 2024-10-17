/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:07:23 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/17 11:48:47 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* int	draw_2d_map(t_map *map, t_data *data)
{
	char	*pixels;
	int		draw_x;
	int		draw_y;
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
		draw_y = 3 * y * 2500;
		x = 0.;
		while (x < width)
		{
			draw_x = 3 * x;
			if (map->map[x][y] == '1')
			{
				((int *)pixels)[draw_x + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 1 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500  + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500 + 1 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500 + 2 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500 * 2 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500 * 2 + 1 + draw_y] = (0xfff5ff);
				((int *)pixels)[draw_x + 2500  * 2 + 2 + draw_y] = (0xfff5ff);
			}
			else if (!find_player(map->map[x][y]))
			{
				((int *)pixels)[draw_x + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 1 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500  + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500 + 1 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500 + 2 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500 * 2 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500 * 2 + 1 + draw_y] = (0xf02d00);
				((int *)pixels)[draw_x + 2500  * 2 + 2 + draw_y] = (0xf02d00);
			}
			else if (map->map[x][y] == 'F')
			{
				((int *)pixels)[draw_x + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 1 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500  + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500 + 1 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500 + 2 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500 * 2 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500 * 2 + 1 + draw_y] = (0x003eff);
				((int *)pixels)[draw_x + 2500  * 2 + 2 + draw_y] = (0x003eff);
			}
			x += 1;
		}
		y += 1;
	}
	return (0);
} */


int	draw_2d_map(t_map *map, t_data *data)
{
	char	*pixels;
	int		draw_x;
	int		draw_y;
	int		x;
	int		y;
	int		new_y;
	int		new_x;
	int		width;
	int		height;

	printf("x = %i & y = %i\n", map->size->x, map->size->y);
	width = map->size->x;
	height = map->size->y;
	pixels = data->img.addr;
	//pixels += (data->width * 2048) + (data->width * 2); // offset to show in center of screen
	y = 0.;
	while (y < 1300)
	{
		new_y = y / 16;
		draw_y = y * 2500;
		x = 0.;
		while (x < 2500)
		{
			draw_x = x;
			new_x = x / 16;
			if (new_x < width && new_y < height)
			{
				if (map->map[new_x][new_y] == '1')
					((int *)pixels)[draw_x + draw_y] = (0xfff5ff);
				else if (!find_player(map->map[new_x][new_y]))
					((int *)pixels)[draw_x + draw_y] = (0xf02d00);
				else if (map->map[new_x][new_y] == 'F')
					((int *)pixels)[draw_x + draw_y] = (0x003eff);
			}
			x += 1;
		}
		y += 1;
	}
	return (0);
}