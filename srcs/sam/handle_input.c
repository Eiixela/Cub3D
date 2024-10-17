/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:01:13 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/18 00:42:26 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_new_image(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	data->img.ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr, \
		&data->img.bit_per_pixel, &data->img.line_len, &data->img.endian);
	draw_new_2d(data->map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
}

int	handle_keyboard(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (handle_win_exit(data));
	else if (keysym == 'w')
	{
		data->map->player_position->y -= 1;
		draw_new_image(data);
	}
	else if (keysym == 's')
	{
		data->map->player_position->y += 1;
		draw_new_image(data);
	}
	else if (keysym == 'a')
	{
		data->map->player_position->x -= 1;
		draw_new_image(data);
	}
	else if (keysym == 'd')
	{
		data->map->player_position->x += 1;
		draw_new_image(data);
	}
	return (0);
}

	// This part of the code is not reachable a the moment because it makes the minimap disapear of the screen
