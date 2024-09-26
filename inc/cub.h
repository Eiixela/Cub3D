/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:13:52 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/26 13:58:57 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <stdbool.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "libft.h"

# define BUFFER_SIZE 100

/* enum
{
	ESC = 27,
}; */

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_map
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		ceiling_c[3];
	int		floor_c[3];
	char	**map;
	
}	t_map;

/* struct s_gc
{
	void	*ptr;
	void	*next;
} t_gc; */


//PARING
int	parsing(int ac, char **av, t_map *map);

//extension_check
int	file_check(char *file, t_map *map);

//GNL
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif