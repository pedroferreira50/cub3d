/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:00:28 by pviegas-          #+#    #+#             */
/*   Updated: 2023/11/13 13:38:55 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*templst;
	t_list	*next;

	if (*lst == NULL || del == NULL)
		return ;
	templst = *lst;
	next = NULL;
	while (templst != NULL)
	{
		next = templst->next;
		del(templst->content);
		free(templst);
		templst = next;
	}
	*lst = NULL;
}
