/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:22:53 by aljulien          #+#    #+#             */
/*   Updated: 2024/11/08 10:22:57 by aljulien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	tmp = NULL;
	head = malloc(sizeof(t_list));
	if (!head || !lst)
		return (NULL);
	head->content = f(lst->content);
	tmp = head;
	while (lst->next)
	{
		tmp->next = malloc(sizeof(t_list));
		if (!tmp->next)
			return (ft_lstclear(&head, del), NULL);
		tmp = tmp->next;
		lst = lst->next;
		tmp->content = f(lst->content);
	}
	tmp->next = NULL;
	return (head);
}
