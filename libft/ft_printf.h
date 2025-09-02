/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:13:45 by pviegas-          #+#    #+#             */
/*   Updated: 2023/11/14 16:50:49 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>

int	ft_base_ul(unsigned long long nbr, char *base);
int	ft_base_u(unsigned int nbr, char *base);
int	ft_base(int nbr, char *base);
int	ft_printf(const char *str, ...);

#endif
