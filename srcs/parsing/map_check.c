/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/09 15:06:16 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

	if (has_zero_at_border((*map)->map, (*map)->map_height))
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
