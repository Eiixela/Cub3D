/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:11:15 by saperrie          #+#    #+#             */
/*   Updated: 2024/11/11 09:17:52 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	mlx_cleanup(t_data *data)
{
	int	i;

	i = 0;
	if (data->img.ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	while (i < 4 && data->tex[i].ptr)
		mlx_destroy_image(data->mlx_ptr, data->tex[i++].ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	return ;
}

static void	keys_init(t_data *data)
{
	data->keys->w = 0;
	data->keys->s = 0;
	data->keys->a = 0;
	data->keys->d = 0;
	data->keys->right = 0;
	data->keys->left = 0;
}

void	data_init(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
	data->width, data->height, "smol wolf 3d");
	data->img.ptr = mlx_new_image(data->mlx_ptr, data->width, \
		data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr, \
		&data->img.bit_per_pixel, &data->img.line_len, &data->img.endian);
	keys_init(data);
	mlx_hook(data->win_ptr, EXIT_CROSS, 0, &handle_win_exit, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, &handle_key_press, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, &handle_key_release, data);
	mlx_loop_hook(data->mlx_ptr, &key_loop, data);
}
