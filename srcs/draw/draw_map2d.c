/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:34:35 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/26 22:16:22 by saperrie         ###   ########.fr       */
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

static void	init_map2d(t_map2d *map2d, t_map *map)
{
	map2d->map_offset_x = (map->player_position->x * SQUARE_SIZE) - \
	(VISIBLE_MAP_SIZE / 2);
	map2d->map_offset_y = (map->player_position->y * SQUARE_SIZE) - \
	(VISIBLE_MAP_SIZE / 2);
	map2d->screen_y = 0;
	map2d->screen_x = 0;
}

static int	get_map_color(char current_char, int x, int y, t_map *map)
{
	if (current_char == '1')
		return (DARK_PINK);
	if (player_position(x, y, map) == 0)
		return (PASTEL_PURPLE);
	if (current_char == 'F' || current_char == 'N' || current_char == 'S' \
		|| current_char == 'W' || current_char == 'E' || current_char == '0')
		return (LIGHT_PINK);
	return (0);
}

static void	draw_map_pixel(t_data *data, t_map2d *map2d, t_map *map)
{
	int		color;
	int		map_x;
	int		map_y;
	char	current_char;

	map_x = (map2d->screen_x + map2d->map_offset_x) / SQUARE_SIZE;
	map_y = (map2d->screen_y + map2d->map_offset_y) / SQUARE_SIZE;
	if (map_x >= 0 && map_x < map->size->y \
		&& map_y >= 0 && map_y < map->size->x)
	{
		current_char = map->map[map_y][map_x];
		color = get_map_color(current_char, map2d->screen_x + \
		map2d->map_offset_x, map2d->screen_y + map2d->map_offset_y, map);
		((int *)data->img.addr)[map2d->screen_y * WIDTH + map2d->screen_x] \
		= color;
		if ((current_char == '0' || current_char == '1')
			&& ((map2d->screen_x + map2d->map_offset_x) % SQUARE_SIZE == 0 \
			|| (map2d->screen_y + map2d->map_offset_y) % SQUARE_SIZE == 0) \
			&& current_char != '0')
			((int *)data->img.addr)[map2d->screen_y * WIDTH + \
				map2d->screen_x] = GRID_COLOR;
	}
	else
		((int *)data->img.addr)[map2d->screen_y * WIDTH + map2d->screen_x] = 0;
}

int	draw_map2d(t_map *map, t_data *data)
{
	t_map2d	map2d;

	init_map2d(&map2d, map);
	while (map2d.screen_y < VISIBLE_MAP_SIZE)
	{
		map2d.screen_x = 0;
		while (map2d.screen_x < VISIBLE_MAP_SIZE)
		{
			draw_map_pixel(data, &map2d, map);
			map2d.screen_x++;
		}
		map2d.screen_y++;
	}

	return (0);
}
