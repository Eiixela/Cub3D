/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:52:48 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/11 09:39:58 by saperrie         ###   ########.fr       */
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
		y += 1;
	}
	while (y < HEIGHT * WIDTH)
	{
		((int *)pixels)[y] = (int)floor;
		y += 1;
	}
}

void	draw_image(t_data *data, bool first_image)
{
	draw_ceiling_and_floor(data);
	draw_all_rays(data, data->map);
	draw_map2d(data->map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	if (first_image == 1)
		mlx_loop(data->mlx_ptr);
}
