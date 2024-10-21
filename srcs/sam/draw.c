/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:07:23 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/21 11:18:17 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	player_position(int new_x, int new_y, t_map *map)
{
	if (new_x == map->player_position->x && new_y == map->player_position->y)
		return (0);
	return (1);
}

int	player_precision(t_data *data, int *x, int *y)
{
	int p_y;
	int p_x;

	
}

int draw_new_2d(t_map *map, t_data *data)
{
    char    *pixels;
    int     draw_x, draw_y, x, y, new_y, new_x, width, height;
    int     square_size = 64; // Size of each square

    width = map->size->y;
    height = map->size->x;
    pixels = data->img.addr;
    y = 0;
    while (y < HEIGHT)
    {
		//p_y = y / 10;
        new_y = y / square_size;
        draw_y = y * WIDTH;
        x = 0;
        while (x < WIDTH)
        {
            draw_x = x;
            new_x = x / square_size;
            //p_x = x / 10;
			if (new_x < width && new_y < height)
            {
                char current_char = map->map[new_y][new_x];
                int color;
                if (current_char == '1')
                    color = PINK;
                else if (player_position(new_x, new_y, map) == 0)
				{
					player_precision(data, &x, &y);
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

