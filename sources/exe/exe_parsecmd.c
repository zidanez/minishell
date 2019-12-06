/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_parsecmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 12:02:55 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:26:22 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "sys_tool.h"

static int	exe_parsecmd_err(char *str, int fl)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(str, 2);
	if (fl == 1)
		ft_putendl_fd(" command not found", 2);
	if (fl == 2)
		ft_putendl_fd(" not binary", 2);
	return (0);
}

int			exe_parsecmd(char *str, t_env *env, char **path)
{
	if ((str[0] == '/') || (str[0] == '.' && str[1] == '/'))
	{
		if (sys_file_exist(str))
		{
			if (sys_file_type(str) == FILE_BIN)
			{
				(*path) = ft_strdup(str);
				return (1);
			}
			else
				return (exe_parsecmd_err(str, 2));
		}
	}
	else if (((*path) = find_bin(env, str)) != NULL)
		return (1);
	return (exe_parsecmd_err(str, 1));
}
