/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:19:18 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/06 13:21:23 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	check_color_value(t_map *map)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (255 < (map)->floor_c[i] || 0 > (map)->floor_c[i])
		{
			printf("Colors values are not in 0-255 range\n");
			free_map(map);
			return (false);
		}
		if (255 < (map)->ceiling_c[i] || 0 > (map)->ceiling_c[i])
		{
			printf("Colors values are not in 0-255 range\n");
			free_map(map);
			return (false);
		}
		i++;
	}
	return (true);
}

t_map	*check_for_color(t_map *map)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (map->ceiling_c[i] == -1 || map->floor_c[i] == -1)
			return (free_map(map), NULL);
		i++;
	}
	return (map);
}

int	color_cmp(char *line)
{
	if (line && (ft_strncmp("F ", line, 2) == 0 \
		|| ft_strncmp("C ", line, 2) == 0))
		return (0);
	return (1);
}

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
