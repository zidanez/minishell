/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 04:21:28 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:15:07 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <dirent.h>

static int	bltn_cd_rmlast(t_dlist **path)
{
	t_dlist *last;
	char	*str;
	int		counter;

	counter = 0;
	str = (char *)(*path)->content;
	if (ft_strequ(str, "\0"))
		return (1);
	last = (*path);
	while (last->next != NULL)
	{
		last = last->next;
		counter++;
	}
	if (counter == 0)
		ft_dlst_delcut(path, et_rm_str);
	else
		ft_dlst_delcut(&last, et_rm_str);
	return (1);
}

static void	bltn_cd_create_new_path(t_dlist **path, char *str)
{
	bltn_cd_destroy_path(&(*path));
	(*path) = ft_dlstnew(str, ft_strlen(str) + 1);
}

static int	bltn_cd_setglobals(t_env *env, DSTRING **newpath,\
								DSTRING **oldpath, t_dlist **path)
{
	ft_avl_set(env->globals,\
				ft_avl_node("OLDPWD", g_cd_pwd->txt, g_cd_pwd->strlen + 1));
	ft_avl_set(env->globals,\
				ft_avl_node("PWD", (*newpath)->txt, (*newpath)->strlen + 1));
	dstr_del(&g_oldpwd);
	g_oldpwd = dstr_new(g_cd_pwd->txt);
	dstr_del(&g_pwd);
	g_pwd = dstr_new((*newpath)->txt);
	bltn_cd_freepaths(oldpath, newpath, path);
	return (0);
}

int			bltn_cd_loop(char *args, t_env *env, t_flags *fl)
{
	t_dlist	*path;
	DSTRING	*newpath;
	DSTRING	*oldpath;

	path = NULL;
	if (ft_strequ(args, "."))
		return (0);
	bltn_cd_parser(env, &path);
	oldpath = bltn_cd_pathtostr(path);
	if (ft_strequ(args, ".."))
		bltn_cd_rmlast(&path);
	else
	{
		if (args[0] != '/')
			ft_dlstpush(&path, ft_dlstnew(args, ft_strlen(args) + 1));
		else
			bltn_cd_create_new_path(&path, args);
	}
	newpath = bltn_cd_pathtostr(path);
	if (fl->first)
		bltn_cd_flgspath(&newpath);
	if (chdir((char *)newpath->txt) == -1)
		return (bltn_cd_error(&oldpath, &newpath, &path));
	return (bltn_cd_setglobals(env, &newpath, &oldpath, &path));
}

int			bltn_cd(char **args, t_env *env)
{
	t_flags	fl;

	ft_bzero(&fl, sizeof(t_flags));
	g_cd_pwd = dstr_new(g_pwd->txt);
	g_cd_oldpwd = dstr_new(g_oldpwd->txt);
	if (bltn_cd_countargs(args) != 1 && (bltn_cd_countargs(args) < 3\
		|| args[1][0] == '-'))
		return (bltn_cd_argrec(&args[1], &args[2], env, &fl));
	else if (bltn_cd_countargs(args) != 1)
		ft_putendl_fd("minishell: cd : too many arguments", 2);
	else
		return (bltn_cd_home(env));
	return (0);
}
