/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:32:46 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/26 13:48:56 by aljulien         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_map	map;

	
	if (!parsing(ac, av, &map))
	{
		printf("ok!\n");
		return (0);
	}
	printf("hmmm...\n");
	return (1);
	//t_vars	vars;
	/* vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "cub");
	mlx_hook(vars.win, 02, 1L<<0, close_win, &vars);
	mlx_loop(vars.mlx); */
}
