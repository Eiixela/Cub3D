/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:22:17 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/13 14:22:41 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	count_array_size(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	*fill_color_tab(int	*color_tab)
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

static int	is_num_color(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!((color[i] >= '0' && color[i] <= '9') \
			|| color[i] == ' ' || color[i] == '\t'))
			return (0);
		i++;
	}
	return (1);
}

static int	*fill_color_int(char **color, int *color_tab, t_map *map)
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
		if (!is_num_color(color[i]))
			return (printf("Invalid color value\n"), free_map(map), NULL);
		if (color_tab[i] == -4000000)
			return (printf("Invalid color value\n"), free_map(map), NULL);
		i++;
	}
	return (color_tab);
}

t_map	*fill_color(char *line, char *path, \
	t_map *map, t_vector2D *colours_found)
{
	char	**color;

	if (ft_strncmp("F ", line, 2) == 0)
	{
		color = ft_split(path, ',');
		if (!color)
			return (NULL);
		colours_found->x++;
		map->floor_c = fill_color_int(color, map->floor_c, map);
		free_dtab(color);
		if (!map->floor_c || !check_color_value(map))
			return (free_map(map), NULL);
	}
	else if (ft_strncmp("C ", line, 2) == 0)
	{
		color = ft_split(path, ',');
		if (!color)
			return (NULL);
		colours_found->y++;
		map->ceiling_c = fill_color_int(color, map->ceiling_c, map);
		free_dtab(color);
		if (!map->ceiling_c || !check_color_value(map))
			return (free_map(map), NULL);
	}
	return (map);
}
