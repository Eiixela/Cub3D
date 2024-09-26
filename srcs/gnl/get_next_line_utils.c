/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:01:55 by aljulien          #+#    #+#             */
/*   Updated: 2024/09/26 12:33:33 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n)
	{
		*str++ = 0;
		--n;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	total;

	if (nmemb == 0 || size == 0)
		return (NULL);
	total = nmemb * size;
	if (nmemb != 0 && ((total / nmemb) != size))
		return (0);
	p = malloc (total);
	if (!p)
		return (NULL);
	ft_bzero(p, total);
	return (p);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*s;
	unsigned int	len_s1;
	unsigned int	len_s2;
	size_t			i;
	size_t			j;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	if ((char) c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
