/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amajid <amajid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:13:33 by amajid            #+#    #+#             */
/*   Updated: 2023/11/07 14:56:34 by amajid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*last;

	if (!lst || !(*lst) || !del)
		return ;
	current = (*lst);
	while (current->next)
	{
		if (current->content)
			del(current->content);
		last = current;
		current = current->next;
		free(last);
	}
	if (current->content)
		del(current->content);
	last = current;
	current = current->next;
	free(last);
	(*lst) = NULL;
	return ;
}
