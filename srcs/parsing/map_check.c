/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/10 16:16:59 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fill(t_map *map, t_point size, t_point cur, char to_fill)
{
	if (cur.y < 0 || cur.y >= ft_strlen(map->map[cur.x]) || cur.x < 0 || cur.x >= map->size->x || map->map[cur.y][cur.x] != to_fill)
		return ;
	map->map[cur.y][cur.x] = 'F';
	fill(map, size, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(map, size, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(map, size, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(map, size, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	flood_fill(t_map *map, t_point size, t_point begin)
{
	fill(map, size, begin, '0');
}

int	player_way(t_map **map)
{
	int		i;
	int		j;
	int		count_player;

	i = 0;
	j = 0;
	count_player = 0;
	(*map)->player_position = malloc(sizeof(t_point));
	if (!(*map)->player_position)
		return (0);
	while ((*map)->map[i])
	{
		while ((*map)->map[i][j])
		{
			if (!find_player((*map)->map[i][j]))
			{
 				(*map)->player_position->x = i;
				(*map)->player_position->y = j;
				count_player++;		
				(*map)->player_way = (*map)->map[i][j];
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (count_player);
}

int	map_good(t_map **map)
{
	int i = 0;
	while ((*map)->map[i])
	{
		printf("%s\n", (*map)->map[i]);
		i++;
	}
	i = player_way(map);
	if (!i || i > 1)
		return (printf("Please make sure there's one player on the map\n"), 1);
	printf("%i and %i\n", (*map)->player_position->x, (*map)->player_position->x);
 	flood_fill((*map), *(*map)->size, *(*map)->player_position);
		//return (printf("Map invalid, please make sur the map in surrounded by walls only\n"), 1);
	if (check_char_map(map))
		return (printf("Invalid character in map\n"), 1);
	return (0);
}
