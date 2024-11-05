/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:52:48 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/05 13:58:52 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void	draw_first_image(t_data *data)
{
	data->img.ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr, \
	&data->img.bit_per_pixel, &data->img.line_len, &data->img.endian);
	draw_ceiling_and_floor(data);
	draw_all_rays(data, data->map);
	draw_map2d(data->map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
}

void	draw_new_image(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	data->img.ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr, \
		&data->img.bit_per_pixel, &data->img.line_len, &data->img.endian);
	draw_ceiling_and_floor(data);
	draw_all_rays(data, data->map);
	draw_map2d(data->map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
}
