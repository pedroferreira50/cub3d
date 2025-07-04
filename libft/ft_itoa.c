/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:00:15 by pviegas-          #+#    #+#             */
/*   Updated: 2023/11/13 13:42:27 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int value)
{
	if (value < 0)
		return (-value);
	else
		return (value);
}

static int	isnegative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static int	countint(int n)
{
	int	length;
	int	size;

	length = 0;
	size = n;
	while (size != 0)
	{
		size = size / 10;
		length++;
	}
	if (n == 0)
		length = 1;
	return (length);
}

static void
	ft_strrev(char *str)
{
	size_t	length;
	size_t	i;
	char	tmp;

	length = ft_strlen(str);
	i = 0;
	while (i < length / 2)
	{
		tmp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tmp;
		i++;
	}
}

char
	*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	size_t	neg;

	neg = isnegative(n);
	str = ft_calloc(countint(n) + neg + 1, sizeof(*str));
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	i = 0;
	while (n != 0)
	{
		str[i++] = '0' + ft_abs((n % 10));
		n = (n / 10);
	}
	if (neg == 1)
		str[i] = '-';
	ft_strrev(str);
	return (str);
}

/*
int	main(void)
{
	int a = 1234;
	char	*str = ft_itoa(a);
	printf("%s", str);
	free(str);
	return (0);
}*/