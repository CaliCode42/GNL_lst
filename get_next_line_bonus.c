/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:53:17 by tcali             #+#    #+#             */
/*   Updated: 2025/01/27 11:55:11 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

void	free_set_null(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

void	read_file(int fd, t_list *list)
{
	char	*temp;
	char	*buffer;

	buffer = malloc(sizeof(char) * 1);
	if (!buffer)
		return ;
	buffer[0] = '\0';
	while (list->bytes_read > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
			return (free(buffer));
		list->bytes_read = read(fd, temp, BUFFER_SIZE);
		temp[list->bytes_read] = '\0';
		buffer = ft_join_free(buffer, temp);
		if (!buffer)
			return ;
		if (ft_strlen(buffer) == 0)
			return (free(buffer));
	}
	free_set_null(list->buf);
	list->buf = ft_strdup(buffer);
	if (!list->buf)
		return ;
	free_set_null(buffer);
}

void	ft_parse_line(t_list *list)
{
	char	*new_line_index;

	if (!list || !list->buf)
		return ;
	list->new_line = NULL;
	if (ft_strchr(list->buf, '\n') != NULL)
	{
		new_line_index = ft_strchr(list->buf, '\n');
		list->new_line = ft_strdup(new_line_index + 1);
		if (!list->new_line)
			return ;
		*new_line_index = '\0';
	}
	if (list->line != NULL)
		list->line = ft_join_free(list->line, list->buf);
	else
	{
		list->line = ft_strdup(list->buf);
		free(list->buf);
		list->buf = NULL;
		if (!list->line)
			return ;
	}
	if (!list->line && list->new_line)
		return (free(list->new_line));
}

char	*get_next_line(int fd)
{
	static t_list	fd_list[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	fd_list[fd].buf = NULL;
	fd_list[fd].bytes_read = 1;
	read_file(fd, &fd_list[fd]);
	if (fd_list[fd].buf == NULL)
		return (NULL);
	fd_list[fd].line = NULL;
	if (fd_list[fd].new_line)
	{
		fd_list[fd].line = ft_strdup(fd_list[fd].new_line);
		if (!fd_list[fd].line)
			return (free(fd_list[fd].new_line), NULL);
		free(fd_list[fd].new_line);
		fd_list[fd].new_line = NULL;
	}
	ft_parse_line(&fd_list[fd]);
	if (fd_list[fd].bytes_read == 0 && !fd_list[fd].new_line
		&& (!fd_list[fd].line || !*fd_list[fd].line))
		return (NULL);
	if (fd_list[fd].line == NULL && fd_list[fd].buf)
		return (free(fd_list[fd].buf), NULL);
	return (fd_list[fd].line);
}
