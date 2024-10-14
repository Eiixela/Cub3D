/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:38:01 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/14 08:56:24 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	valid_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == -32 || c == -9)
		return (0);
	return (1);
}

int	find_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

int	check_char_map(t_map **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*map)->map[i])
	{
		while ((*map)->map[i][j])
		{
			if (valid_char((*map)->map[i][j]))
				return (1);
			if ((*map)->map[i][j] == ' ')
				(*map)->map[i][j] = '0';
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
