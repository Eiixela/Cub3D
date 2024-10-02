/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/02 14:38:34 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	check_horizontal_borders(char **map, int height)
{
	int	first_row_width;
	int	last_row_width;
	int	j;

	first_row_width = ft_strlen(map[0]);
	j = 0;
	while (j < first_row_width)
	{
		if (map[0][j] != '1')
			return (true);
		j++;
	}
	last_row_width = ft_strlen(map[height - 1]);
	j = 0;
	while (j < last_row_width)
	{
		if (map[height - 1][j] != '1')
			return (true);
		j++;
	}
	return (false);
}

bool	check_vertical_borders(char **map, int height)
{
	int	i;
	int	row_width;

	i = 0;
	while (i < height)
	{
		row_width = ft_strlen(map[i]);
		if (map[i][0] != '1' || map[i][row_width - 1] != '1')
			return (true);
		i++;
	}
	return (false);
}

bool	check_borders(char **map, int height)
{
	if (check_horizontal_borders(map, height))
		return (true);
	if (check_vertical_borders(map, height))
		return (true);
	return (false);
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

	if (check_borders((*map)->map, (*map)->map_height))
	{
		printf("Map invalid\n");
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
