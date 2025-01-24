/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:41:55 by tcali             #+#    #+#             */
/*   Updated: 2025/01/24 16:03:02 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

void	read_file(int fd, t_list *list)
{
	char	*temp;
	char	*buffer;

	buffer = malloc(sizeof(char) * 1);
	if (!buffer)
		return ;
	//printf("in read_file : buffer is malloc'd\n");
	buffer[0] = '\0';
	while (list->bytes_read > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
		{
			//printf("in read_file : buffer is free'd\n");
			return (free(buffer));
		}
		//printf("in read_file : temp is malloc'd\n");
		list->bytes_read = read(fd, temp, BUFFER_SIZE);
		if (list->bytes_read < 0)
		{
			//printf("in read_file : temp is free'd\n");
			//printf("in read_file : buffer is free'd\n");
			return (free(temp), free(buffer));
		}
		temp[list->bytes_read] = '\0';
		//printf("\n\ntemp : [%s]\n", temp);
		//printf("\n\nbuffer : [%s]\n", buffer);
		buffer = ft_join_free(buffer, temp);
		//printf("in read_file : temp is free'd\n");
		//printf("in read_file : buffer is free'd then malloc'd\n");
		if (!buffer)
			return ;
		if (ft_strlen(buffer) == 0)
			return (free(buffer));
	}
	if (list->buf)
	{
		free(list->buf);
		list->buf = NULL;
	}
	list->buf = ft_strdup(buffer);
	//printf("error seems to be here\n");
	if (!list->buf)
		return ;
	free(buffer);
	//printf("in read_file : buffer is free'd\n");
	buffer = NULL;
	return ;
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
		//printf("in ft_parse_line : list->new_line is malloc'd\n");
		if (!list->new_line)
			return ;
		*new_line_index = '\0';
	}
	/*else if (!ft_strchr(list->buf, '\n'))
		list->new_line = NULL;*/
	if (list->line != NULL)
	{
		list->line = ft_join_free(list->line, list->buf);
		//printf("in ft_parse_line : list->buf is free'd\n");
		//printf("in ft_parse_line : list->line is free'd then malloc'd\n");
	}
	else
	{
		list->line = ft_strdup(list->buf);
		if (!list->line)
		{
			free(list->buf);
			list->buf = NULL;
			return ;
		}
		//printf("in ft_parse_line : list->line is malloc'd\n");
		free(list->buf);
		list->buf = NULL;
		//printf("in ft_parse_line : list->buf is free'd\n");
	}
	if (!list->line && list->new_line)
	{
		//printf("in ft_parse_line : list->new_line is free'd\n");
		return (free(list->new_line));
	}
}

char	*get_next_line(int fd)
{
	static t_list	list;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	list.buf = NULL;
	list.bytes_read = 1;
	read_file(fd, &list);
	//printf("\n\nlist.buf : [%s]\n", list.buf);
	if (list.buf == NULL)
		return (NULL);
	if (list.line)
	{
		//free(list.line);
		list.line = NULL;
	}
	if (list.new_line)
	{
		list.line = ft_strdup(list.new_line);
		//printf("in get_next_line : list.line is malloc'd\n");
		if (!list.line)
		{
			//printf("in get_next_line : list.line is free'd\n");
			return (free(list.new_line), NULL);
		}
		//printf("in get_next_line : list.new_line is free'd\n");
		free(list.new_line);
		list.new_line = NULL;
	}
	ft_parse_line(&list);
	if (list.bytes_read == 0 && !list.new_line && (!list.line || !*list.line))
		return (NULL);
	if (list.line == NULL && list.buf)
	{
		//printf("in get_next_line : list.buf is free'd\n");
		return (free(list.buf), NULL);
	}
	return (list.line);
}
