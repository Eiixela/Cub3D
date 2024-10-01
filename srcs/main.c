/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:32:46 by aljulien          #+#    #+#             */
/*   Updated: 2024/10/01 15:37:38 by aljulien         ###   ########.fr       */
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

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		free(map->north);
		free(map->south);
		free(map->east);
		free(map->west);
		if (map->map)
		{
			i = 0;
			while (i < map->map_height && map->map[i])
			{
				free(map->map[i]);
				i++;
			}
			free(map->map);
		}
		free(map->ceiling_c);
		free(map->floor_c);
		free(map);
	}
}

int	main(int ac, char **av)
{
	t_map	*map;
	int i = 0;

	map = init_map();
	if (!map)
		return (1);
	if (!parsing(ac, av, &map))
	{
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
		while (i < map->map_height)
		{
			printf("%s\n", map->map[i]);
			i++;
		}
		printf("ok!\n");
		free_map(map);
		return (0);
	}
	printf("hmmm...\n");
	free_map(map);
	return (1);
	//t_vars	vars;
	/* vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "cub");
	mlx_hook(vars.win, 02, 1L<<0, close_win, &vars);
	mlx_loop(vars.mlx); */
}
