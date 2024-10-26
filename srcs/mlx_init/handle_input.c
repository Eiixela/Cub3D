/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:01:13 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/27 00:27:39 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	mlx_cleanup(t_data *data)
{
	if (data->img.ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	return ;
}

int	handle_win_exit(t_data *data)
{
	mlx_loop_end(data->mlx_ptr);
	mlx_cleanup(data);
	free_map(data->map);
	exit(0);
}

int	handle_key_press(int keysym, t_data *data)
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
	else if (keysym == XK_Left)
		data->keys->left = 1;
	else if (keysym == XK_Right)
		data->keys->right = 1;
	return (0);
}

int	handle_key_release(int keysym, t_data *data)
{
	if (keysym == 'w')
		data->keys->w = 0;
	else if (keysym == 's')
		data->keys->s = 0;
	else if (keysym == 'a')
		data->keys->a = 0;
	else if (keysym == 'd')
		data->keys->d = 0;
	else if (keysym == XK_Left)
		data->keys->left = 0;
	else if (keysym == XK_Right)
		data->keys->right = 0;
	return (0);
}

int	key_loop(t_data *data)
{
	if (data->keys->left == 1)
		left_arrow(data);
	if (data->keys->right == 1)
		right_arrow(data);
	if (data->keys->w == 1)
		w_key(data);
	if (data->keys->s == 1)
		s_key(data);
	if (data->keys->a == 1)
		a_key(data);
	if (data->keys->d == 1)
		d_key(data);
	draw_new_image(data);
	return (0);
}
