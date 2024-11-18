/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:23:32 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/14 11:31:59 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const t_vector_int	*s;
	t_vector_int		*d;

	if (!dest && !src)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	s = (t_vector_int *)src;
	d = (t_vector_int *)dest;
	while (n--)
		d[n] = s[n];
	return (dest);
}
