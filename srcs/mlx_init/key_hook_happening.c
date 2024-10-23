/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_happening.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:56:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/23 15:56:25 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	left_arrow(t_data *data)
{
	data->map->player_position->angle -= 0.04;
	if (data->map->player_position->angle < 0)
		data->map->player_position->angle += 2 * PI;
	data->map->player_position->dx = cos(data->map->player_position->angle) * 5;
	data->map->player_position->dy = sin(data->map->player_position->angle) * 5;
}

void	right_arrow(t_data *data)
{
	data->map->player_position->angle += 0.04;
	if (data->map->player_position->angle > 2 * PI)
		data->map->player_position->angle -= 2 * PI;
	data->map->player_position->dx = cos(data->map->player_position->angle) * 5;
	data->map->player_position->dy = sin(data->map->player_position->angle) * 5;
}

void	s_key(t_data *data)
{
	float move_speed;
	float new_x;
	float new_y;

	move_speed = 0.064;
	new_y = data->map->player_position->y + -sin(data->map->player_position->angle) * move_speed;
	new_x = data->map->player_position->x + -cos(data->map->player_position->angle) * move_speed;
	if (data->map->map[(int)new_y][(int)data->map->player_position->x] != '1' &&
		data->map->map[(int)data->map->player_position->y][(int)new_x] != '1')
	{
		data->map->player_position->x = new_x;
		data->map->player_position->y = new_y;
	}
	else
		printf("WALL: NORTH\nFACING: SOUTH\n\n");
}

void w_key(t_data *data)
{
	float move_speed;
	float new_x;
	float new_y;

	move_speed = 0.064;
	new_y = data->map->player_position->y + sin(data->map->player_position->angle) * move_speed;
	new_x = data->map->player_position->x + cos(data->map->player_position->angle) * move_speed;
	if (data->map->map[(int)new_y][(int)data->map->player_position->x] != '1' &&
		data->map->map[(int)data->map->player_position->y][(int)new_x] != '1')
	{
		data->map->player_position->x = new_x;
		data->map->player_position->y = new_y;
	}
	else
		printf("WALL: NORTH\nFACING: SOUTH\n\n");
}


void	a_key(t_data *data)
{
	float move_speed = 0.064;
	float new_x = data->map->player_position->x + sin(data->map->player_position->angle) * move_speed;
	float new_y = data->map->player_position->y - cos(data->map->player_position->angle) * move_speed;

	if (data->map->map[(int)new_y][(int)data->map->player_position->x] != '1' &&
		data->map->map[(int)data->map->player_position->y][(int)new_x] != '1')
	{
		data->map->player_position->x = new_x;
		data->map->player_position->y = new_y;
	}
	else
		printf("WALL: COLLISION (RIGHT)\n\n");
}

void	d_key(t_data *data)
{
	float move_speed = 0.064;
	float new_x = data->map->player_position->x - sin(data->map->player_position->angle) * move_speed;
	float new_y = data->map->player_position->y + cos(data->map->player_position->angle) * move_speed;

	if (data->map->map[(int)new_y][(int)data->map->player_position->x] != '1' &&
		data->map->map[(int)data->map->player_position->y][(int)new_x] != '1')
	{
		data->map->player_position->x = new_x;
		data->map->player_position->y = new_y;
	}
	else
		printf("WALL: COLLISION (LEFT)\n\n");
}
