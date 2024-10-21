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

void draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
        if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT)
            ((int *)data->img.addr)[y1 * WIDTH + x1] = color;
        if (x1 == x2 && y1 == y2)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}

int	player_position(double new_x, double new_y, t_map *map)
{
	(void)map;
	double player_y_middle = map->player_position->y * SQUARE_SIZE;
	double player_x_middle = map->player_position->x * SQUARE_SIZE;
	if ((new_y <=(player_y_middle + (PLAYER_SIZE/2 + 2)) && new_y >= (player_y_middle - (PLAYER_SIZE/2 + 2)) && new_x <= (player_x_middle + (PLAYER_SIZE/2 + 2)) && new_x >= (player_x_middle - (PLAYER_SIZE/2 + 2))))
		return (0);
	return (1);
}


int draw_new_2d(t_map *map, t_data *data)
{
	char	*pixels;
	double	 draw_x, draw_y, x, y, new_y, new_x, width, height;
	int	color;

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
				char	current_char = map->map[(int)new_y][(int)new_x];
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

	int player_x = map->player_position->x * SQUARE_SIZE;
    int player_y = map->player_position->y * SQUARE_SIZE;
    int line_length = 30; // Adjust this value to change the line length
    int end_x = player_x + cos(map->player_position->angle) * line_length;
    int end_y = player_y + sin(map->player_position->angle) * line_length;

    draw_line(data, player_x, player_y, end_x, end_y, RED); // You can change RED to any color you prefer
	return (0);
}
