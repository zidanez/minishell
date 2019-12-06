/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd_home.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:08:02 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 16:25:02 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	bltn_cd_home_set(t_env *env, DSTRING **path)
{
	DSTRING	*tmp;

	ft_avl_set(env->globals,\
				ft_avl_node("OLDPWD", g_pwd->txt, g_pwd->strlen + 1));
	ft_avl_set(env->globals,\
				ft_avl_node("PWD", (*path)->txt, (*path)->strlen + 1));
	tmp = dstr_new(g_pwd->txt);
	dstr_del(&g_pwd);
	dstr_del(&g_oldpwd);
	g_pwd = dstr_new((*path)->txt);
	g_oldpwd = dstr_new(tmp->txt);
	dstr_del(&g_cd_oldpwd);
	dstr_del(&g_cd_pwd);
	dstr_del(path);
	dstr_del(&tmp);
	return (0);
}

static int	bltn_cd_home_err(DSTRING **path)
{
	ft_putendl("minishell: cd : Redirection error");
	dstr_del(path);
	return (0);
}

int			bltn_cd_home(t_env *env)
{
	DSTRING	*path;

	if (ft_avl_search(env->globals, "HOME") != NULL)
	{
		path = env_get_variable("HOME", env);
		if (chdir((char *)path->txt) == -1)
			return (bltn_cd_home_err(&path));
		return (bltn_cd_home_set(env, &path));
	}
	return (0);
}
