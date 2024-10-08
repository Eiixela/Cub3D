/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/08 16:09:08 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


bool check_borders(char **map, int map_height)
{
	int	i;
	size_t	j;
	size_t	new_j;

	i = 0;
	j = 0;
	new_j = 0;
	printf("%s\n", map[3]);
	while (map[i])
	{
		while (map[i][j] == ' ' || map[i][j] == '\t')
			j++;
		new_j = j;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				j++;
			if (i == 0 || !map[i - 1][j] || map[i - 1][j] == ' ')
				if (map[i][j] != '1')
					return (false);
			if (i == map_height - 1 || !map[i + 1][j] || map[i + 1][j] == ' ')
				if (map[i][j] != '1')
					return (false);
			if (j == ft_strlen(map[i]) || !map[i][j + 1] || map[i][j + 1] == ' ')
				if (map[i][j] != '1')
					return (false);
			if (j == new_j || !map[i][j - 1] || map[i][j - 1] == ' ')
				if (map[i][j] != '1')
					return (false);
			j++;
		}
		j = 0;
		i++;
	}
	return (true);
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

	if (!check_borders((*map)->map, (*map)->map_height))
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
