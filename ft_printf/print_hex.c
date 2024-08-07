/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:47:28 by angerard          #+#    #+#             */
/*   Updated: 2024/06/20 12:32:23 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_hex(unsigned long long num, char *base)
{
	char	hex_buffer[16];
	int		i;
	int		count;

	if (num == 0)
	{
		ft_putchar(base[0]);
		return (1);
	}
	i = 0;
	while (num != 0)
	{
		hex_buffer[i++] = base[num % 16];
		num = num / 16;
	}
	count = 0;
	while (i > 0)
	{
		i--;
		ft_putchar(hex_buffer[i]);
		count++;
	}
	return (count);
}
