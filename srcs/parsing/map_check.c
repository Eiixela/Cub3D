/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/09 15:35:19 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//Basic flood_fill function 
typedef struct	s_point
{
	int x;
	int y;
} t_point;

void	fill(char **tab, t_point cur, char to_fill, int i)
{
	if (cur.y < 0 || cur.y >= ft_strlen(tab) || cur.x < 0 || cur.x >= size.x || tab[cur.y][cur.x] != to_fill)
		return;
	tab[cur.y][cur.x] = 'F';
	fill(tab, (t_point){cur.x - 1, cur.y}, to_fill);
	fill(tab, (t_point){cur.x + 1, cur.y}, to_fill);
	fill(tab, (t_point){cur.x, cur.y - 1}, to_fill);
	fill(tab, (t_point){cur.x, cur.y + 1}, to_fill);
}

void	flood_fill(char **map, t_point size, t_point begin)
{
	fill(map, begin, map[begin.y][begin.x]);
}

int	player_way(t_map **map)
{
	int	i;
	int	j;
	int	count_player;

	i = 0;
	j = 0;
	count_player = 0;
	while ((*map)->map[i])
	{
		while ((*map)->map[i][j])
		{
			if (!find_player((*map)->map[i][j]))
			{
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
	int	player;

 	if (flood_fill((*map)->map, /*player position,*/, '0', 0))
	{
		printf("Map invalid, please make sur the map in surrounded by walls only\n");
		return (1);
	}
	if (check_char_map(map))
	{
		printf("Invalid character in map\n");
		return (1);
	}
	player = player_way(map);
	if (!player || player > 1)
	{
		printf("Please make sure there's one player on the map\n");
		return (1);
	}
	return (0);
}
