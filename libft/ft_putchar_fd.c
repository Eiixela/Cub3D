/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_putchar_fd.c:+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: aljulien <aljulien@student.42lyon.fr>  +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2023/11/11 21:39:36 by alexie#+##+# */
/*   Updated: 2023/11/14 21:19:12 by aljulien ###   ########.fr   */
/**/
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
