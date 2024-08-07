/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:43:46 by angerard          #+#    #+#             */
/*   Updated: 2024/06/20 12:32:39 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static int	ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (0);
}

static char	*init_empty_string(void)
{
	char	*str;

	str = malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

static void	extract_nxline(char **buffer, int eol)
{
	char	*tmp;

	tmp = *buffer;
	*buffer = ft_substr(*buffer, eol, ft_strlen(*buffer));
	ft_free(&tmp);
	return ;
}

static ssize_t	read_line_from_file(int fd, char **buffer)
{
	ssize_t	bytes_read;
	char	*read_buff;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	if (!(*buffer))
		*buffer = init_empty_string();
	if (!(*buffer))
		return (0);
	read_buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buff)
		return (ft_free(buffer), 0);
	bytes_read = read(fd, read_buff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		read_buff[bytes_read] = '\0';
		*buffer = ft_strjoin(*buffer, read_buff);
		if (is_in_str(*buffer, '\n') >= 0)
			break ;
		bytes_read = read(fd, read_buff, BUFFER_SIZE);
	}
	ft_free(&read_buff);
	if (bytes_read < 0)
		return (ft_free(buffer));
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			eol;

	if (fd < 0 || BUFFER_SIZE <= 0 || !read_line_from_file(fd, &buffer))
		return (NULL);
	eol = is_in_str(buffer, '\n');
	if (eol >= 0)
	{
		line = ft_substr(buffer, 0, eol + 1);
		extract_nxline(&buffer, eol + 1);
	}
	else
	{
		line = ft_substr(buffer, 0, ft_strlen(buffer));
		ft_free(&buffer);
	}
	if (*line == '\0')
		return (ft_free(&line), ft_free(&buffer), NULL);
	return (line);
}
