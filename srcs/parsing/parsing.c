/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:36:34 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/01 16:53:12 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_map_edges(t_map *map)
{
	int	i;
//	int	map_line_lenght;

	i = 0;
	if (map->map[i])
	{
		while(map->map[0][i])
		{
			if (map->map[0][i] != 49)
				return (1);
			i++;
		}
		i = 0;
		while (map->map[i][0])
		{
			if (map->map[i][0] != 49)
				return (1);
			i++;			
		}
	}
	return (0);
}

int	map_good(t_map *map)
{
	if (check_map_edges(map))
	{
		printf("Map invalid\n");
		return (1);
	}
	return (0);
}

int	parsing(int ac, char **av, t_map **map)
{
	if (ac != 2)
		return (1);
	if (ac == 2)
	{
		if (file_check(av[1], map))
			return (1);
		if (map_good(*map))
			return (1);
	}
	return (0);
}
