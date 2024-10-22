/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_happening.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:56:15 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/22 11:10:02 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	left_arrow(t_data *data)
{
	data->map->player_position->angle -= 0.06;
	if (data->map->player_position->angle < 0)
		data->map->player_position->angle += 2 * PI;
	data->map->player_position->dx = cos(data->map->player_position->angle) * 5;
	data->map->player_position->dy = sin(data->map->player_position->angle) * 5;
}

void	right_arrow(t_data *data)
{
	data->map->player_position->angle += 0.06;
	if (data->map->player_position->angle > 2 * PI)
		data->map->player_position->angle -= 2 * PI;
	data->map->player_position->dx = cos(data->map->player_position->angle) * 5;
	data->map->player_position->dy = sin(data->map->player_position->angle) * 5;
}

void	s_key(t_data *data)
{
	if (data->map->map[(int)(data->map->player_position->y + 0.19)]
		[(int)data->map->player_position->x] == '1')
	{
		printf("WALL: SOUTH\nFACING: NORTH\n\n");
		return ;
	}
	data->map->player_position->y += 0.064;
}

void	w_key(t_data *data)
{
	if (data->map->map[(int)(data->map->player_position->y - 0.19)]
		[(int)data->map->player_position->x] == '1')
	{
		printf("WALL: NORTH\nFACING: SOUTH\n\n");
		return ;
	}
	data->map->player_position->y -= 0.064;
}

void	a_key(t_data *data)
{
	if (data->map->map[(int)data->map->player_position->y]
		[(int)(data->map->player_position->x - 0.19)] == '1')
	{
		printf("WALL: WEST\nFACING: EAST\n\n");
		return ;
	}
	data->map->player_position->x -= 0.064;
}

void	d_key(t_data *data)
{
	if (data->map->map[(int)data->map->player_position->y]
		[(int)(data->map->player_position->x + 0.19)] == '1')
	{
		printf("WALL: EAST\nFACING: WEST\n\n");
		return ;
	}
	data->map->player_position->x += 0.064;
}
