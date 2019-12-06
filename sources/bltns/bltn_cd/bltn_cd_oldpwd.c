/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd_oldpwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 14:08:15 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 14:08:36 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	bltn_cd_oldpwd_set(t_env *env, DSTRING **path)
{
	ft_avl_set(env->globals,\
				ft_avl_node("OLDPWD", g_pwd->txt, g_pwd->strlen + 1));
	ft_avl_set(env->globals,\
				ft_avl_node("PWD", (*path)->txt, (*path)->strlen + 1));
	dstr_del(&g_oldpwd);
	g_oldpwd = dstr_new(g_pwd->txt);
	dstr_del(&g_pwd);
	g_pwd = dstr_new((*path)->txt);
	dstr_del(path);
	dstr_del(&g_cd_oldpwd);
	dstr_del(&g_cd_pwd);
	return (0);
}

static int	bltn_cd_oldpwd_err(DSTRING **path)
{
	ft_putendl_fd("minishell: cd: Redirection error", 2);
	dstr_del(path);
	return (0);
}

int			bltn_cd_oldpwd(t_env *env)
{
	DSTRING *tmp;

	tmp = dstr_new(g_oldpwd->txt);
	if (chdir((char *)tmp->txt) == -1)
		return (bltn_cd_oldpwd_err(&tmp));
	return (bltn_cd_oldpwd_set(env, &tmp));
	return (0);
}
