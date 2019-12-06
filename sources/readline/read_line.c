/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:35:37 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:36:36 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		read_line_error(void)
{
	ft_putendl_fd("minishell: readline() malloc error!", 2);
	exit(0);
}

static char		*ft_realoc(char *str, int size)
{
	char		*tmp_line;

	if (!(tmp_line = (char *)malloc(sizeof(char) * size)))
	{
		free(str);
		return (NULL);
	}
	tmp_line = ft_strcpy(tmp_line, str);
	free(str);
	return (tmp_line);
}

static void		repose(int *bufsize, char **buf)
{
	(*bufsize) += MSH_RL_BUFSIZE;
	buf = ft_realloc((*buf), (*bufsize));
	if (!buf || !(*buf))
		read_line_error();
}

char			*read_line(void)
{
	char		*buf;
	char		ch;
	int			bufsize;
	int			pos;
	int			red;

	pos = 0;
	bufsize = MSH_RL_BUFSIZE;
	if (!(buf = (char *)malloc(sizeof(char) * MSH_RL_BUFSIZE)))
		read_line_error();
	while ((red = read(1, &ch, 1)) > 0)
	{
		if (ch == '\n')
		{
			buf[pos] = '\0';
			return (buf);
		}
		else
			buf[pos] = ch;
		pos++;
		if (pos >= MSH_RL_BUFSIZE)
			repose(&bufsize, &buf);
	}
	return (NULL);
}
