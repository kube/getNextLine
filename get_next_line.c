/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kube <kube@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 09:15:38 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/02/07 16:15:42 by kube             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*static void					display_buffer_line(t_bufferlist *fdbuffer)
{
	t_buffer				*current;

	printf("############BUFFERLINE##############\n");
	current = fdbuffer->buffer;
	while (current)
	{
		printf("%s", current->text);
		if (current->next == fdbuffer->buffer || current->is_line_end)
			break;
		current = current->next;
	}
	printf("\n");
	printf("############BUFFRLINE##############\n");
}*/


static void					pop_line(t_bufferlist *fdbuffer, char **line,
										unsigned int length)
{
	t_buffer				*current;
	unsigned int			i;
	unsigned int			k;

	*line = (char*)malloc(length * sizeof(char));
	current = fdbuffer->buffer;
	i = 0;
	while ((current = fdbuffer->buffer) && i < length)
	{
		k = 0;
		while (current->text[k])
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

static void					fill_buffer(int fd, t_bufferlist *bufferlist,
										t_buffer **buffer)
{
	unsigned int			i;
	unsigned int			length;
	char					*cache;
	t_buffer				*node;

	// printf("fill_buffer\n");

	cache = (char*)malloc((BUFF_SIZE + 1) * sizeof(char));
	read(fd, cache, BUFF_SIZE);
	cache[BUFF_SIZE] = 0;
	i = 0;
	length = 0;
	while (cache[i] || i == BUFF_SIZE)
	{
		if (cache[i] == '\n' || i == BUFF_SIZE)
		{
			cache[i] = 0;
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
			node->is_line_end = (i != BUFF_SIZE);
			(*buffer)->prev->next = node;
			(*buffer)->prev = node;
			bufferlist->lines_left += (i != BUFF_SIZE);
			length = 0;
		}
		else
			length++;
		i++;
	}
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

static void					look_buffer(t_bufferlist *fdbuffer)
{
	t_buffer				*current;

	current = fdbuffer->buffer;
	printf("\n");
	printf("\n");
	while (current)
	{
		printf("% *d", current->length, current->length);
		if (current->next == fdbuffer->buffer || current->is_line_end)
			break;
		current = current->next;
	}
	printf("\n");
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
		/// CHECK 
		while (fdbuffer->lines_left == 0)
		{
			fill_buffer(fd, fdbuffer, &fdbuffer->buffer);
		}
		look_buffer(fdbuffer);
		length = 0;
		current = fdbuffer->buffer;
		while (current)
		{
			length += current->length;
			if (current->next == fdbuffer->buffer || current->is_line_end)
				break;
			current = current->next;
		}
		// display_buffer_line(fdbuffer);
		pop_line(fdbuffer, line, length);
		return (0);
	}
	return (1);
}
