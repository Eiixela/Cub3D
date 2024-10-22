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
	double		draw_x, draw_y, x, y, new_y, new_x, width, height, angle;
	t_vector2D	player_coor;

	width = map->size->y;
	height = map->size->x;
	pixels = data->img.addr;
	color = 0;
	y = 0;
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
					color = PINK;
				else if (player_position(x, y, map) == 0)
					color = PASTEL_PURPLE;
				else if (current_char == '0')
					color = LIME_GREEN;
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
	player_coor.x = map->player_position->x * SQUARE_SIZE;
	player_coor.y = map->player_position->y * SQUARE_SIZE;
	angle = map->player_position->angle;
	int i = 0;
	while (i < 60)
	{
		draw_line(data, player_coor, &angle, RED);
		angle += 0.03;
		i++;
	}
	//printf("%f\n", distance);
	//draw_rays(data);
	return (0);
}
