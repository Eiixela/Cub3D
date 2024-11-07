/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/07 14:43:09 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	player_where(t_map *map, int *player_y, int *player_x)
{
	int	x;
	int	y;
	int	count_player;

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
				map->map[x][y] = '0';
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

	player_x = 0;
	player_y = 0;
	if (check_char_map(&map))
		return (printf("Invalid character on map\n"), 1);
	if (player_where(map, &player_x, &player_y) != 1)
		return (printf("Too many players on map\n"), 1);
	player->x = player_x;
	player->y = player_y;
	map->player_position->x = player_x + 0.5;
	map->player_position->y = player_y + 0.5;
	if (iter_flood_fill(map))
		return (printf("Please make sure the map is fully closed\n"), 1);
	set_angle_view(map);
	map->map[player_y][player_x] = '0';
	return (0);
}
