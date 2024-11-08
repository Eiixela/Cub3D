/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling_floor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:50:26 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/08 13:18:03 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static unsigned int	rgb_to_hex(int rgb[3])
{
	unsigned int	result;
	int				i;
	int				value;

	result = 0;
	i = 0;
	while (i < 3)
	{
		value = rgb[i];
		if (value < 0)
			value = 0;
		if (value > 255)
			value = 255;
		result = (result << 8) | value;
		i++;
	}
	return (result);
}

void	draw_ceiling_and_floor(t_data *data)
{
	char	*pixels;
	int		ceiling;
	int		floor;
	int		y;

	y = 0;
	pixels = data->img.addr;
	ceiling = rgb_to_hex(data->map->ceiling_c);
	floor = rgb_to_hex(data->map->floor_c);
	while (y < HEIGHT * WIDTH >> 1)
	{
		((int *)pixels)[y] = (int)ceiling;
		y++;
	}
	while (y < HEIGHT * WIDTH)
	{
		((int *)pixels)[y] = (int)floor;
		y++;
	}
}
