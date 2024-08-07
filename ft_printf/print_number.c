/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:47:00 by angerard          #+#    #+#             */
/*   Updated: 2024/06/20 12:32:19 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	print_pos_num(unsigned long num)
{
	char	num_buffer[12];
	int		i;
	int		count;

	if (num == 0)
	{
		ft_putchar('0');
		return (1);
	}
	i = 0;
	while (num != 0)
	{
		num_buffer[i++] = num % 10 + '0';
		num = num / 10;
	}
	count = 0;
	while (i > 0)
	{
		i--;
		ft_putchar(num_buffer[i]);
		count++;
	}
	return (count);
}

int	print_number(long num)
{
	int	count;

	count = 0;
	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
		count = 1;
	}
	count += print_pos_num(num);
	return (count);
}
