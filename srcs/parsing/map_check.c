/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/16 15:39:57 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	player_where(t_map *map, int *player_x, int *player_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->size->y)
	{
		x = 0;
		while (map->map[y][x])
		{
			if (!find_player(map->map[y][x]))
			{
				*player_x = x;
				*player_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	is_border(t_map *map, int x, int y)
{
	return (x == 0 || y == 0 || y == map->size->y - 1 \
		|| map->map[y][x + 1] == '\0');
}

static int	flood_fill(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->size->y || x < 0 || !map->map[y][x])
		return (0);
	if (map->map[y][x] == '1' || map->map[y][x] == 'F')
		return (0);
	if (is_border(map, x, y))
		return (1);
	map->map[y][x] = 'F';
	if (flood_fill(map, x - 1, y) || flood_fill(map, x + 1, y) \
		|| flood_fill(map, x, y - 1) || flood_fill(map, x, y + 1))
		return (1);
	return (0);
}

int	map_good(t_map *map, t_player *player)
{
	int	player_x;
	int	player_y;

	if (!player_where(map, &player_x, &player_y))
		return (1);
	player->x = player_x;
	player->y = player_y;
	if (flood_fill(map, player_x, player_y))
		return (1);
	return (0);
}
