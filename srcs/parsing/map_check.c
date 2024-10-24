/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/24 13:57:32 by aljulien         ###   ########.fr       */
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
				map->player_way = map->map[x][y];
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

static void	set_angle_view(t_map *map)
{
	if (map->player_way == 'N')
		map->player_position->angle = 3 * PI / 2;
	if (map->player_way == 'S')
		map->player_position->angle = PI / 2;
	if (map->player_way == 'E')
		map->player_position->angle = 0;
	if (map->player_way == 'W')
		map->player_position->angle = PI;
}

int	map_good(t_map *map, t_player *player)
{
	int	player_x;
	int	player_y;

/* 	if (check_char_map(&map))
	{
		printf("HERE!\n");
		return (1);
	} */
	if (player_where(map, &player_x, &player_y) != 1)
		return (1);
	player->x = player_x;
	player->y = player_y;
	map->player_position->x = player_x;
	map->player_position->y = player_y;
	if (flood_fill(map, player_x, player_y))
		return (1);
	set_angle_view(map);
	map->map[player_y][player_x] = '0';
	return (0);
}
