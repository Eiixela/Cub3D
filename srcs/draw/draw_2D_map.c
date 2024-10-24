/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:34:35 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/24 20:02:37 by saperrie         ###   ########.fr       */
/*                                                                            */
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

#define VISIBLE_MAP_SIZE 200

static void init_draw_params(t_draw_params *params, t_map *map)
{
	params->map_offset_x = (map->player_position->x * SQUARE_SIZE) - (VISIBLE_MAP_SIZE / 2);
	params->map_offset_y = (map->player_position->y * SQUARE_SIZE) - (VISIBLE_MAP_SIZE / 2);
	params->screen_y = 0;
	params->screen_x = 0;
}

static int get_map_color(char current_char, int x, int y, t_map *map)
{
	if (current_char == '1')
		return (DARK_PINK);
	if (player_position(x, y, map) == 0)
		return (PASTEL_PURPLE);
	if (current_char == 'F' || current_char == 'N' || current_char == 'S' ||
		current_char == 'W' || current_char == 'E' || current_char == '0')
		return (LIGHT_PINK);
	return (0);
}

static void draw_map_pixel(t_data *data, t_draw_params *params, t_map *map)
{
	int color;
	int map_x, map_y;
	char current_char;

	map_x = (params->screen_x + params->map_offset_x) / SQUARE_SIZE;
	map_y = (params->screen_y + params->map_offset_y) / SQUARE_SIZE;
	if (map_x >= 0 && map_x < map->size->y && map_y >= 0 && map_y < map->size->x)
	{
		current_char = map->map[map_y][map_x];
		color = get_map_color(current_char, params->screen_x + params->map_offset_x,
			params->screen_y + params->map_offset_y, map);
		((int *)data->img.addr)[params->screen_y * WIDTH + params->screen_x] = color;
		if ((current_char == '0' || current_char == '1') &&
			((params->screen_x + params->map_offset_x) % SQUARE_SIZE == 0 ||
			(params->screen_y + params->map_offset_y) % SQUARE_SIZE == 0) &&
			current_char != '0')
			((int *)data->img.addr)[params->screen_y * WIDTH + params->screen_x] = GRID_COLOR;
	}
	else
		((int *)data->img.addr)[params->screen_y * WIDTH + params->screen_x] = 0;
}

static void draw_player_direction(t_data *data, t_map *map)
{
	int player_screen_x, player_screen_y, end_x, end_y;
	int line_length;

	player_screen_x = VISIBLE_MAP_SIZE / 2;
	player_screen_y = VISIBLE_MAP_SIZE / 2;
	line_length = 30;
	end_x = player_screen_x + cos(map->player_position->angle) * line_length;
	end_y = player_screen_y + sin(map->player_position->angle) * line_length;
	draw_line(data, player_screen_x, player_screen_y, end_x, end_y, RED);
}

int draw_new_2d(t_map *map, t_data *data)
{
	t_draw_params params;

	draw_all_rays(data, map);
	init_draw_params(&params, map);
	while (params.screen_y < VISIBLE_MAP_SIZE)
	{
		params.screen_x = 0;
		while (params.screen_x < VISIBLE_MAP_SIZE)
		{
			draw_map_pixel(data, &params, map);
			params.screen_x++;
		}
		params.screen_y++;
	}
	draw_player_direction(data, map);
	return (0);
}



// int	draw_new_2d(t_map *map, t_data *data)
// {
// 	int			color;
// 	char		*pixels, current_char;
// 	double		draw_x, draw_y, x, y, new_y, new_x, width, height;


// 	width = map->size->y;
// 	height = map->size->x;
// 	pixels = data->img.addr;
// 	color = 0;
// 	y = 0;
// 	draw_all_rays(data, map);
// 	while (y < HEIGHT)
// 	{
// 		new_y = y / SQUARE_SIZE;
// 		draw_y = y * WIDTH;
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			draw_x = x;
// 			new_x = x / SQUARE_SIZE;
// 			if (new_x < width && new_y < height)
// 			{
// 				current_char = map->map[(int)new_y][(int)new_x];
// 				if (current_char == '1')
// 					color = DARK_PINK;
// 				else if (player_position(x, y, map) == 0)
// 					color = PASTEL_PURPLE;
// 				else if (current_char == 'F' || current_char == 'N'
// 					|| current_char == 'S' || current_char == 'W'
// 					|| current_char == 'E' || current_char == '0')
// 					color = LIGHT_PINK;
// 				else
// 					color = 0;
// 				((int *)pixels)[(int)draw_x + (int)draw_y] = color;
// 				if ((current_char == '0' || current_char == '1') && \
// 					((int)x % SQUARE_SIZE == 0 || (int)y % SQUARE_SIZE == 0)
// 					&& current_char != '0')
// 					((int *)pixels)[(int)draw_x + (int)draw_y] = GRID_COLOR;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	int player_x = map->player_position->x * SQUARE_SIZE;
//     int player_y = map->player_position->y * SQUARE_SIZE;
//     int line_length = 30; // Adjust this value to change the line length
//     int end_x = player_x + cos(map->player_position->angle) * line_length;
//     int end_y = player_y + sin(map->player_position->angle) * line_length;
//     draw_line(data, player_x, player_y, end_x, end_y, RED);
// 	return (0);
// }
