/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:00:19 by pviegas-          #+#    #+#             */
/*   Updated: 2023/11/13 13:40:06 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*templst;

	if (*lst != NULL)
	{
		templst = *lst;
		while (templst->next != NULL)
			templst = templst->next;
		templst->next = new;
	}
	else
		*lst = new;
}
