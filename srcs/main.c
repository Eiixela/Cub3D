/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:32:46 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/10 13:34:56 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* int	close_win(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
} */

void	free_map_array(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
}

void	free_map(t_map **map)
{
	if (map && *map)
	{
		free((*map)->north);
		free((*map)->south);
		free((*map)->east);
		free((*map)->west);
		if ((*map)->map)
		{
			free_map_array((*map)->map, (*map)->size->x);
			free((*map)->map);
		}
		free((*map)->ceiling_c);
		free((*map)->floor_c);
		free(*map);
		*map = NULL;
	}
}

int	main(int ac, char **av)
{
	t_map	*map;

	map = init_map();
	if (!map)
		return (1);
	if (!parsing(ac, av, &map))
	{
	/*	int i = 0;
	  	printf("c = %i\n", map->ceiling_c[0]);
		printf("c = %i\n", map->ceiling_c[1]);
		printf("c = %i\n", map->ceiling_c[2]);
		printf("f = %i\n", map->floor_c[0]);
		printf("f = %i\n", map->floor_c[1]);
		printf("f = %i\n", map->floor_c[2]);
		printf("north = %s\n", map->north);
		printf("south = %s\n", map->south);
		printf("east = %s\n", map->east);
		printf("west = %s\n", map->west);
		while (i < map->size->x)
		{
			printf("%s\n", map->map[i]);
			i++;
		} 
	  	printf("c = %c\n", map->player_way);*/
		printf("ok!\n");
		free_map(&map);
		return (0);
	}
	printf("hmmm...\n");
	free_map(&map);
	return (1);
	//t_vars	vars;
	/* vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "cub");
	mlx_hook(vars.win, 02, 1L<<0, close_win, &vars);
	mlx_loop(vars.mlx); */
}
