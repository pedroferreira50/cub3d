/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:07:58 by pviegas-          #+#    #+#             */
/*   Updated: 2023/10/03 15:30:15 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] || (char)c == '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

/*
{
 	int	i;

	i = 0;
 	while (s[i])
 	{
 		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
 	}
 	if (s[i] == c)
 		return ((char *)&s[i]);
 	return (NULL);
}*/
