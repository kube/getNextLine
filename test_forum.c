/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_forum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kube <kube@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 11:22:59 by kube              #+#    #+#             */
/*   Updated: 2014/02/08 16:04:48 by kube             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LOOP_NUMBER 100

#include "get_next_line_forum.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int			main(int argc, char **argv)
{
	int		i;
	int		*openedfiles;
	char	*linebuffer;

	openedfiles = (int*)malloc((argc - 1) * sizeof(int));
	i = 1;
	while (i < argc)
	{
		openedfiles[i - 1] = open(argv[i], O_RDONLY);
		i++;
	}
	i = 0;
	while (get_next_line_forum(openedfiles[i % (argc - 1)], &linebuffer))
	{
		printf("%s\n", linebuffer);
		i++;
	}
	return (0);
}
