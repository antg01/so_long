/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:43:16 by angerard          #+#    #+#             */
/*   Updated: 2024/07/04 11:11:43 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

size_t	ft_strlen_sl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*clean_line(char *line)
{
	size_t	len;

	len = ft_strlen_sl(line);
	if (len > 0 && (line[len - 1] == '\n'))
	{
		line[len - 1] = '\0';
	}
	return (line);
}

void	check_file_exists(const char *filename)
{
	FILE	*file;

	file = fopen(filename, "r");
	if (file)
	{
		ft_printf("File '%s' exists.\n", filename);
		fclose(file);
	}
	else
	{
		ft_printf("Error: File '%s' does not exist or cannot be opened: %s\n",
			filename);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
