/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:13:52 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/26 10:37:50 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "libft.h"

enum {
	ESC = 27,
};

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

//PARING
int	parsing(int ac, char **av);

//extension_check
int	file_check(char *file);
int	file_extension_check(char *file);

#endif