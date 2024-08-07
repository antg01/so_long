/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:10:03 by angerard          #+#    #+#             */
/*   Updated: 2024/07/04 11:10:34 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	ft_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = 0;
	while (str[j + 1] != '\0')
		j++;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	num;
	int				i;

	len = ft_num_len(n);
	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	num = n;
	if (n < 0)
		num = -n;
	while (num > 0)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		str[i++] = '-';
	else if (n == 0)
		str[i++] = '0';
	str[i] = '\0';
	return (ft_strrev(str));
}

void	key_count(int keycode, t_vars *vars)
{
	if (keycode == 13 || keycode == 126 || keycode == 1 || keycode == 125
		|| keycode == 0 || keycode == 123 || keycode == 2 || keycode == 124
		|| keycode == 119 || keycode == 65362 || keycode == 115
		|| keycode == 65364 || keycode == 97 || keycode == 65361
		|| keycode == 100 || keycode == 65363)
	{
		vars->moves++;
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = b;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (b);
}
