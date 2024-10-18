/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:01:13 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/18 02:13:45 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_new_image(t_data *data)
{
	// mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	// data->img.ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	// data->img.addr = mlx_get_data_addr(data->img.ptr, \
	// 	&data->img.bit_per_pixel, &data->img.line_len, &data->img.endian);
	draw_new_2d(data->map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	// mlx_loop(data->mlx_ptr);
}

int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (handle_win_exit(data));
	else if (keysym == 'w')
		data->keys->w = 1;
	else if (keysym == 's')
		data->keys->s = 1;
	else if (keysym == 'a')
		data->keys->a = 1;
	else if (keysym == 'd')
		data->keys->d = 1;
	return (0);
}

int	key_release(int keysym, t_data *data)
{
	if (keysym == 'w')
		data->keys->w = 0;
	else if (keysym == 's')
		data->keys->s = 0;
	else if (keysym == 'a')
		data->keys->a = 0;
	else if (keysym == 'd')
		data->keys->d = 0;
	return (0);
}
