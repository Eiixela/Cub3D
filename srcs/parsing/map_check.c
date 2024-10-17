/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/17 11:47:35 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	player_where(t_map *map, int *player_y, int *player_x)
{
	int	x;
	int	y;
	int count_player;

	count_player = 0;
	x = 0;
	while (x < map->size->x)
	{
		y = 0;
		while (map->map[x][y])
		{
			if (!find_player(map->map[x][y]))
			{
				*player_y = y;
				*player_x = x;
				count_player++;
			}
			y++;
		}
		x++;
	}
	return (count_player);
}

static int	is_border(t_map *map, int x, int y)
{
	return (x == 0 || y == 0 || y == map->size->y - 1 \
		|| map->map[y][x + 1] == '\0');
}

static int	flood_fill(t_map *map, int y, int x)
{
	if (x < 0 || x >= map->size->x || y < 0 || !map->map[x][y])
		return (0);
	if (map->map[x][y] == '1' || map->map[x][y] == 'F')
		return (0);
	if (is_border(map, y, x))
		return (1);
	if (!find_player(map->map[x][y]))
		return (0);
	map->map[x][y] = 'F';
	if (flood_fill(map, y - 1, x) || flood_fill(map, y + 1, x) \
		|| flood_fill(map, y, x - 1) || flood_fill(map, y, x + 1))
		return (1);
	return (0);
}

int	map_good(t_map *map, t_player *player)
{
	int	player_x;
	int	player_y;

	if (player_where(map, &player_x, &player_y) != 1)
		return (1);
	player->x = player_x;
	player->y = player_y;
	if (flood_fill(map, player_y, player_x))
		return (1);
	int i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
	return (0);
}
