/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd_helps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:03:08 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 19:35:26 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		bltn_cd_freepaths(DSTRING **oldpath, DSTRING **newpath,\
								t_dlist **path)
{
	dstr_del(oldpath);
	dstr_del(newpath);
	bltn_cd_destroy_path(path);
}

int			bltn_cd_error(DSTRING **oldpath, DSTRING **newpath,\
								t_dlist **path)
{
	if ((access((*newpath)->txt, 0)))
		ft_putendl_fd("minishell : cd : dir not found", 2);
	else if (!(access((*newpath)->txt, 4)))
		ft_putendl_fd("minishell : cd : access error", 2);
	else
		ft_putendl_fd("minishell : cd : is not directory", 2);
	bltn_cd_freepaths(oldpath, newpath, path);
	return (-1);
}

int			bltn_cd_countargs(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void		bltn_cd_concat(char **path)
{
	char	*tmp;

	tmp = ft_strdup((*path));
	free((*path));
	(*path) = ft_strjoin("/", tmp);
	free(tmp);
}

int			bltn_cd_argrec_ret(char ***path, int status, t_env *env)
{
	free_spl(path);
	if (status != -1)
		return (status);
	dstr_del(&g_oldpwd);
	dstr_del(&g_pwd);
	g_pwd = dstr_new(g_cd_pwd->txt);
	g_oldpwd = dstr_new(g_cd_oldpwd->txt);
	dstr_del(&g_cd_oldpwd);
	dstr_del(&g_cd_pwd);
	chdir(g_pwd->txt);
	ft_avl_set(env->globals,\
				ft_avl_node("OLDPWD", g_oldpwd->txt, g_oldpwd->strlen + 1));
	ft_avl_set(env->globals,\
				ft_avl_node("PWD", g_pwd->txt, g_pwd->strlen + 1));
	return (0);
}
