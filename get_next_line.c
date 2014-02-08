/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kube <kube@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 09:15:38 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/02/08 15:23:14 by kube             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static void					pop_line(t_bufferlist *fdbuffer, char **line,
										unsigned int length)
{
	t_buffer				*current;
	unsigned int			i;
	unsigned int			k;

	*line = (char*)malloc(sizeof(char) * (length + 1));
	(*line)[length] = 0;
	current = fdbuffer->buffer;
	i = 0;
	while ((current = fdbuffer->buffer) && i <= length && !(k = 0))
	{
		while (k < current->length)
			(*line)[i++] = current->text[k++];
		current->prev->next = current->next;
		current->next->prev = current->prev;
		if (current == current->next)
			fdbuffer->buffer = NULL;
		else
			fdbuffer->buffer = current->next;
		if (current->is_line_end)
			break;
		else
			free(current->linked_cache);
		free(current);
	}
	free(current);
	fdbuffer->lines_left--;
}

static int					fill_buffer(int fd, t_bufferlist *bufferlist,
										t_buffer **buffer)
{
	int						i;
	int						length;
	char					*cache;
	t_buffer				*node;
	int						cache_len;

	cache = (char*)malloc((BUFF_SIZE + 1) * sizeof(char));
	cache_len = read(fd, cache, BUFF_SIZE);
	if (cache_len <= 0)
		return (0);
	i = 0;
	length = 0;
	while (cache[i] || (i == cache_len && cache[i - 1]))
	{
		if (cache[i] == '\n' || i == cache_len)
		{
			node = (t_buffer*)malloc(sizeof(t_buffer));
			node->text = cache + i - length;
			node->length = length;
			if (!*buffer)
				*buffer = node;
			else
			{
				(*buffer)->prev->next = node;
				node->prev = (*buffer)->prev; 
			}
			(*buffer)->prev = node;
			node->next = *buffer;
			node->linked_cache = cache;
			node->is_line_end = (i != cache_len);
			(*buffer)->prev->next = node;
			(*buffer)->prev = node;
			bufferlist->lines_left += (i != cache_len || cache_len < BUFF_SIZE);
			length = 0;
		}
		else
			length++;
		i++;
	}
	return (1);
}

static t_bufferlist			*get_fdbuffer(int fd, t_bufferlist **bufferlist)
{
	t_bufferlist			*current;
	t_bufferlist			*fdbuffer;

	current = *bufferlist;
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
	fdbuffer->next = *bufferlist;
	*bufferlist = fdbuffer;
	return (fdbuffer);
}

int							get_next_line(int fd, char **line)
{
	static t_bufferlist		*bufferlist = NULL;
	t_bufferlist			*fdbuffer;
	t_buffer				*current;
	unsigned int			length;

	if (fd >= 0)
	{
		fdbuffer = get_fdbuffer(fd, &bufferlist);
		while (fdbuffer->lines_left == 0)
		{
			if (!fill_buffer(fd, fdbuffer, &fdbuffer->buffer))
				return (0);
		}
		length = 0;
		current = fdbuffer->buffer;
		while (current)
		{
			length += current->length;
			if (current->next == fdbuffer->buffer || current->is_line_end)
				break;
			current = current->next;
		}
		pop_line(fdbuffer, line, length);
		return (1);
	}
	return (0);
}
