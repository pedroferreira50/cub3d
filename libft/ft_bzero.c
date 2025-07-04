/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:35:45 by pviegas-          #+#    #+#             */
/*   Updated: 2023/10/05 15:49:01 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n-- > 0)
	{
		*p++ = 0;
	}
}

/*
int	main(void)
{
	char	s1[30] = "123456789";
	char	s2[30] = "123456789";
	unsigned int	s3[30] = {1, 2147483648, 3, 4, 5, 6, 7, 8, 9};
	unsigned int	s4[30] = {1, 2147483648, 3, 4, 5, 6, 7, 8, 9};

	bzero(s3, 5);
	ft_bzero(s4, 5);
	for (int i = 0; i < 10; i++)
	{
            printf("%u", s3[i]);
	}
	printf("\n");
	for (int j = 0; j < 10; j++)
	{
			printf("%u", s4[j]);
	}

	return (0);
}*/