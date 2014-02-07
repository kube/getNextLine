/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kube <kube@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 09:18:03 by cfeijoo           #+#    #+#             */
/*   Updated: 2014/02/03 23:44:44 by kube             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 7

typedef struct			s_buffer
{
	char				*text;
	unsigned int		length;
	struct s_buffer		*next;
	struct s_buffer		*prev;
	int					is_line_end;
	char				*linked_cache;
}						t_buffer;

typedef struct			s_bufferlist
	{
	t_buffer			*buffer;
	int					fd;
	unsigned int		lines_left;
	struct s_bufferlist	*next;
}						t_bufferlist;
int						get_next_line(int fd, char **line);

#endif
