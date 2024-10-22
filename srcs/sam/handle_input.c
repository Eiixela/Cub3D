/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 00:01:13 by saperrie          #+#    #+#             */
/*   Updated: 2024/10/22 15:39:12 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int rgb_to_hex(int rgb[3])
{
    unsigned int result = 0;

    for (int i = 0; i < 3; i++) {
        // Clamp the value between 0 and 255
        int value = rgb[i];
        if (value < 0) value = 0;
        if (value > 255) value = 255;
        result = (result << 8) | value;
    }
    return result;
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
	while (y < HEIGHT * WIDTH * 0.5)
		((int *)pixels)[y++] = (int)ceiling;
	while (y < HEIGHT * WIDTH)
		((int *)pixels)[y++] = (int)floor;
}

void	draw_new_image(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	data->img.ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.ptr, \
		&data->img.bit_per_pixel, &data->img.line_len, &data->img.endian);
	draw_ceiling_and_floor(data);
	draw_new_2d(data->map, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
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
	else if (keysym == XK_Left)
		data->keys->left = 1;
	else if (keysym == XK_Right)
		data->keys->right = 1;	
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
	else if (keysym == XK_Left)
		data->keys->left = 0;
	else if (keysym == XK_Right)
		data->keys->right = 0;
	return (0);
}
