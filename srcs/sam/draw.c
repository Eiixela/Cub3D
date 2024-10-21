/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   draw.c	 :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: saperrie <saperrie@student.42.fr>	  +#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2024/10/16 16:07:23 by saperrie	  #+#	#+#	 */
/*   Updated: 2024/10/21 11:22:48 by saperrie	 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#include "cub.h"

int	player_position(int new_x, int new_y, t_map *map)
{
	(void)map;
	int player_y_middle = map->player_position->y * 64 + 64 / 2;
	int player_x_middle = map->player_position->x * 64 + 64 / 2;
	if ((new_y <=(player_y_middle + 10/2) && new_y >= (player_y_middle - 10/2) && new_x <= (player_x_middle + 10/2) && new_x >= (player_x_middle - 10/2)))
		return (0);
	return (1);
	// if (new_x == map->player_position->x && new_y == map->player_position->y)
	// 	return (0);
	// return (1);
}


int draw_new_2d(t_map *map, t_data *data)
{
	char	*pixels;
	int	 draw_x, draw_y, x, y, new_y, new_x, width, height;
	int	 square_size = 64; // Size of each square

	width = map->size->y;
	height = map->size->x;
	pixels = data->img.addr;
	y = 0;
	while (y < HEIGHT)
	{
		new_y = y / square_size;
		draw_y = y * WIDTH;
		x = 0;
		while (x < WIDTH)
		{
			draw_x = x;
			new_x = x / square_size;
			if (new_x < width && new_y < height)
			{
				char	current_char = map->map[new_y][new_x];
				int	color;
				if (current_char == '1')
					color = PINK;
				else if (player_position(x, y, map) == 0)
				{
					// player_precision(data, &new_x, &new_y);

					color = PASTEL_PURPLE;
				}
				else if (current_char == '0')
					color = LIME_GREEN;
				else
					color = 0;
				((int *)pixels)[draw_x + draw_y] = color;
				if ((current_char == '0' || current_char == '1') && \
					(x % square_size == 0 || y % square_size == 0))
					((int *)pixels)[draw_x + draw_y] = GRID_COLOR;
			}
			x++;
		}
		y++;
	}
	return (0);
}
