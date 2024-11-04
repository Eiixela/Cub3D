/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/05 13:47:40 by aljulien         ###   ########.fr       */
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
/* 
//TODO work in progress
static	int	iter_flood_fill(t_map *map, int x, int y)
{
	t_queue queue;
	
	queue.point = malloc(sizeof(t_queue) * 8);
	if (!queue.point)
		return (1);
	queue.point[0].x = x;
	queue.point[0].y = y;
	queue.reading_index = 0;
	queue.writing_index = 0;
	while (1) //while(reading_index == writing_index)
	{
		printf("%f%f  ", queue.point[0].x, queue.point[0].y);
		add_to_queue(map, queue);
		/* 
		resize si queue trop petite
		 */

		/* 
		if indice valide, on ajoute les copains de l'indice dans la queue
		 */

		/* 
		else indice pas bon donc on break le while (1)
		 */
	/* 	if (is_border(map, (int)queue.point.x, (int)queue.point.y))
			return (1);
		
	}
}*/

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

	player_x = 0;
	player_y = 0;
 	if (check_char_map(&map))
		return (printf("Invalid char on map.\n"), 1);
	if (player_where(map, &player_x, &player_y) != 1)
		return (printf("Only one player on the map is allowed.\n"), 1);
	player->x = player_x;
	player->y = player_y;
	map->player_position->x = player_x;
	map->player_position->y = player_y;
	if (flood_fill(map, player_x, player_y))
		return (printf("Please make sure the map is fully closed.\n"), 1);
	set_angle_view(map);
	map->map[player_y][player_x] = '0';
	return (0);
}
