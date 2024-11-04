/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:32:46 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/05 13:51:47 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_map_array(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}
}

void	free_map(t_map *map)
{
	if (map)
	{
		if (map->north)
		{
			free(map->north);
			map->north = NULL;
		}
		if (map->east)
		{
			free(map->east);
			map->east = NULL;
		}
		if (map->south)
		{
			free(map->south);
			map->south = NULL;
		}
		if (map->west)
		{
			free(map->west);
			map->west = NULL;
		}
		if (map->map)
		{
			free_map_array(map->map, map->size->x + 1);
			free(map->map);
			map->map = NULL;
		}
		if (map->ceiling_c)
		{
			free(map->ceiling_c);
			map->ceiling_c = NULL;
		}
		if (map->floor_c)
		{
			free(map->floor_c);
			map->floor_c = NULL;
		}
		if (map->size)
		{
			free(map->size);
			map->size = NULL;
		}
		if (map->player_position)
		{
			free(map->player_position);
			map->player_position = NULL;
		}
		map = NULL;
	}
}

int	main(int ac, char **av)
{
	t_map		map;
	t_data		data;
	t_player	player;
	//t_pplane	pplane;
	t_keys		keys;

	data.keys = &keys;
	if (!init_map(&map))
		return (1);
	if (!parsing(ac, av, &map, &player))
	{
		/* if (big_init(&data, &player, &pplane, &map) == 1)
			return (1);
		draw_first_image(&data);
		free_map(&map); */
		printf("o!\n");
	}
	else
		return (printf("Error...\n"), free_map(&map), 1);
	return (0);
}
