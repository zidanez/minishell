/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:33:38 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/03 18:13:05 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				bltn_pwd(char **arg, t_env *env)
{
	char	*flgs;
	char	buf[1024];

	env = 0;
	flgs = ft_parse_flags(arg);
	if (flgs && ft_strrchr(flgs, 'P') != NULL)
	{
		getcwd(buf, sizeof(buf));
		ft_putendl(buf);
	}
	else
		ft_putendl(g_pwd->txt);
	if (flgs)
		free(flgs);
	return (0);
}
