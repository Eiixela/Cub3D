/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:22:17 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/13 09:44:32 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	count_array_size(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	*fill_color_tab(int	*color_tab)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		color_tab[i] = -1;
		i++;
	}
	return (color_tab);
}

static int	*fill_color_int(char **color, int *color_tab, \
	int *all_colour_found, t_map *map)
{
	long	i;

	i = count_array_size(color);
	if (i != 3)
	{
		printf("Please check the colors are there\n");
		color_tab = fill_color_tab(color_tab);
		return (free_map(map), NULL);
	}
	i = 0;
	while (i < 3)
	{
		if (color[i])
			color_tab[i] = ft_atoll(color[i]);
		if (color_tab[i] == -4000000)
			return (printf("Invalid color value\n"), free_map(map), NULL);
		i++;
	}
	*all_colour_found += 1;
	return (color_tab);
}

t_map	*fill_color(char *line, char *path, t_map *map, int *colours_found)
{
	char	**color;

	if (ft_strncmp("F ", line, 2) == 0)
	{
		color = ft_split(path, ',');
		if (!color)
			return (NULL);
		map->floor_c = fill_color_int(color, map->floor_c, colours_found, map);
		free_dtab(color);
		if (!map->floor_c || !check_color_value(map))
			return (free_map(map), NULL);
	}
	else if (ft_strncmp("C ", line, 2) == 0)
	{
		color = ft_split(path, ',');
		if (!color)
			return (NULL);
		map->ceiling_c = fill_color_int(color, \
			map->ceiling_c, colours_found, map);
		free_dtab(color);
		if (!map->ceiling_c || !check_color_value(map))
			return (free_map(map), NULL);
	}
	return (map);
}
