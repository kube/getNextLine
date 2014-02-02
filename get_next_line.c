/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kube <kube@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 09:15:38 by cfeijoo           #+#    #+#             */
/*   Updated: 2013/12/25 11:50:19 by kube             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// We're gonna need ft_strdup, ft_strnew, ft_strcat

void						pop_line(t_buffer **buffer, char **line)
{
	t_buffer				*current;
	unsigned int			length;

	length = 0;
	current = *buffer;
	while (current && current->text != NULL)
	{
		length += current->length;
		current = current->next;
	}
	free(*line);
	*line = ft_strnew(length);
	current = *buffer;
	while (current && current->text != NULL)
	{
		ft_strcat(*line, current->text);
		current = current->next;
		// Should free the previous buffer
	}
	*buffer = current;
}

void						fill_buffer(int fd, t_bufferlist *bufferlist,
										t_buffer *buffer)
{
	unsigned int			i;
	unsigned int			length;
	char					*cache;
	t_buffer				*current;

	// HERE WE NEED TO WORK !

	cache = (char*)malloc((BUFF_SIZE + 1) * sizeof(char));
	while (current && current->next)
		current = current->next;
	read(fd, cache, BUFF_SIZE);
	i = 0;
	while (cache[i])
	{
		length = 0;
		while (cache[i] && cache[i] != '\n')
		{
			length++;
			i++;
		}
		current->next = (t_buffer*)malloc(sizeof(t_buffer));
		current = current->next;
		current->next = NULL;
		current->text = ft_strndup((char*)(buffer + i - length), length);
		current->length = length;
		if (cache[i] == '\n')
		{
			// Add a line separator to buffer
			current->next = (t_buffer*)malloc(sizeof(t_buffer));
			current = current->next;
			current->next = NULL;
			current->text = NULL;
			current->length = 0;
			bufferlist->lines_left = bufferlist->lines_left + 1;
			i++;
		}
	}
	free(buffer);
}

t_bufferlist				*get_fdbuffer(int fd, t_bufferlist **bufferlist)
{
	t_bufferlist			*current;
	t_bufferlist			*fdbuffer;

	current = bufferlist;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	fdbuffer = (t_bufferlist*)malloc(sizeof(t_bufferlist));
	fdbuffer->buffer = NULL;
	fdbuffer->fd = fd;
	fdbuffer->lines_left = 0;
	fd_buffer->next = *bufferlist;
	*bufferlist = fdbuffer;
	return (fdbuffer);
}

int							get_next_line(int fd, char **line)
{
	static t_bufferlist		*bufferlist = NULL;
	t_buffer				*fdbuffer;

	if (fd >= 0)
	{
		fdbuffer = get_fdbuffer(fd, &bufferlist);
		if (fdbuffer->lines_left == 0)
			fill_buffer(fd, &fdbuffer);
		pop_line(&(fdbuffer->buffer), line);
		fdbuffer->lines_left--;
	}
	else
		return (1);
	return (0);
}
