/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:00:49 by pviegas-          #+#    #+#             */
/*   Updated: 2023/11/13 13:40:55 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*templst;

	if (!f || !del)
		return (NULL);
	newlst = NULL;
	templst = NULL;
	while (lst != NULL)
	{
		templst = ft_lstnew(f(lst->content));
		if (templst == NULL)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, templst);
		lst = lst->next;
	}
	return (newlst);
}
