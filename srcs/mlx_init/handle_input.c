/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:01:13 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/24 19:23:20 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		return (handle_win_exit(data));
	else if (keysym == 'w')
	{
		printf("PRESS\n");
		data->keys->w = 1;
	}
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

int	key_release(int keysym, t_data *data)
{
	if (keysym == 'w')
	{
		printf("RELEASE\n");
		data->keys->w = 0;
	}
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
