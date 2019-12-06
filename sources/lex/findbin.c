/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:32:18 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:27:45 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "sys_tool.h"

static char			*check_bin(char ***split, char *name)
{
	int				i;
	char			*path;
	char			*tmp;

	i = -1;
	while ((*split)[++i])
	{
		path = ft_strjoin((*split)[i], "/");
		tmp = ft_strdup(path);
		free(path);
		path = ft_strjoin(tmp, name);
		free(tmp);
		if (sys_file_type(path) == FILE_BIN)
		{
			free_spl(split);
			return (path);
		}
		free(path);
	}
	free_spl(split);
	return (NULL);
}

char				*find_bin(t_env *env, char *name)
{
	char			**split;
	t_dyn_string	*path;

	if (ft_avl_search(env->globals, "PATH"))
	{
		path = env_get_variable("PATH", env);
		split = ft_strsplit(path->txt, ':');
		dstr_del(&path);
		return (check_bin(&split, name));
	}
	return (NULL);
}
