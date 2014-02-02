/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 09:18:03 by cfeijoo           #+#    #+#             */
/*   Updated: 2013/12/23 10:29:04 by cfeijoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <libft.h>
# define BUFF_SIZE 4096

typedef struct			s_buffer
{
	char				*text;
	unsigned int		length;
	struct s_buffer		*next;
}						t_buffer;

typedef struct			s_bufferlist
{
	t_buffer			*buffer;
	int					fd;
	unsigned int		lines_left;
	struct s_bufferlist	*next;
}						t_bufferlist;

#endif
