/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:34:35 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/24 14:02:53 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	player_position(double new_x, double new_y, t_map *map)
{
	double	player_y_middle;
	double	player_x_middle;

	player_x_middle = map->player_position->x * SQUARE_SIZE;
	player_y_middle = map->player_position->y * SQUARE_SIZE;
	if ((new_y <= (player_y_middle + (PLAYER_SIZE / 2 + 2))
			&& new_y >= (player_y_middle - (PLAYER_SIZE / 2 + 2))
			&& new_x <= (player_x_middle + (PLAYER_SIZE / 2 + 2))
			&& new_x >= (player_x_middle - (PLAYER_SIZE / 2 + 2))))
		return (0);
	return (1);
}

int	draw_new_2d(t_map *map, t_data *data)
{
	int			color;
	char		*pixels, current_char;
	double		draw_x, draw_y, x, y, new_y, new_x, width, height;
	

	width = map->size->y;
	height = map->size->x;
	pixels = data->img.addr;
	color = 0;
	y = 0;
	draw_all_rays(data, map);
	while (y < HEIGHT)
	{
		new_y = y / SQUARE_SIZE;
		draw_y = y * WIDTH;
		x = 0;
		while (x < WIDTH)
		{
			draw_x = x;
			new_x = x / SQUARE_SIZE;
			if (new_x < width && new_y < height)
			{
				current_char = map->map[(int)new_y][(int)new_x];
				if (current_char == '1')
					color = DARK_PINK;
				else if (player_position(x, y, map) == 0)
					color = PASTEL_PURPLE;
				else if (current_char == 'F' || current_char == 'N' || current_char == 'S' || current_char == 'W' || current_char == 'E')
					color = LIGHT_PINK;
				else
					color = 0;
				((int *)pixels)[(int)draw_x + (int)draw_y] = color;
				if ((current_char == '0' || current_char == '1') && \
					((int)x % SQUARE_SIZE == 0 || (int)y % SQUARE_SIZE == 0))
					((int *)pixels)[(int)draw_x + (int)draw_y] = GRID_COLOR;
			}
			x++;
		}
		y++;
	}
	return (0);
}
