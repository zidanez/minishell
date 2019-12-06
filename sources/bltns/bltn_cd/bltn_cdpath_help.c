/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cdpath_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:36:05 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 19:35:14 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	bltn_cdpath_remslash(char **str)
{
	char	*tmp;

	tmp = ft_strsub((*str), 0, ft_strlen((*str)) - 1);
	free((*str));
	(*str) = ft_strdup(tmp);
	free(tmp);
}

int		bltn_cdpath_setgl(t_env *env, DSTRING **newpath)
{
	ft_avl_set(env->globals,\
				ft_avl_node("OLDPWD", g_pwd->txt, g_pwd->strlen + 1));
	ft_avl_set(env->globals,\
				ft_avl_node("PWD", (*newpath)->txt, (*newpath)->strlen + 1));
	dstr_del(&g_oldpwd);
	g_oldpwd = dstr_new(g_pwd->txt);
	dstr_del(&g_pwd);
	g_pwd = dstr_new((*newpath)->txt);
	dstr_del(&g_cd_oldpwd);
	dstr_del(&g_cd_pwd);
	bltn_cd_freepaths(newpath, NULL, NULL);
	return (0);
}

void	bltn_cd_ar(char **str, char **str2, t_flags *fl)
{
	bltn_cd_parse_flgs((*str), fl);
	free((*str));
	(*str) = ft_strdup((*str2));
}

int		bltn_cd_flgspath(DSTRING **newpath)
{
	int		i;
	char	buf[1024];

	if ((i = readlink((*newpath)->txt,\
								buf, sizeof(buf))) > -1)
	{
		buf[i] = '\0';
		dstr_del(newpath);
		(*newpath) = dstr_new("/");
		dstr_insert_str((*newpath), buf, (*newpath)->strlen);
		if (chdir((char *)(*newpath)->txt) == -1)
			return (bltn_cd_error(newpath, NULL, NULL));
		dstr_del(newpath);
		(*newpath) = dstr_new(getcwd(buf, sizeof(buf)));
	}
	return (0);
}

int		bltn_cd_argrec(char **str, char **str2, t_env *env, t_flags *fl)
{
	char	**path;
	int		status;
	int		i;

	i = -1;
	status = 0;
	if ((*str)[0] == '-' && ft_strlen((*str)) == 1)
		return (bltn_cd_oldpwd(env));
	if ((*str)[0] == '-')
		bltn_cd_ar(str, str2, fl);
	if (ft_strequ((*str), "/"))
		return (bltn_cd_loop((*str), env, fl));
	path = ft_strsplit((*str), '/');
	if ((*str)[0] == '/')
		bltn_cd_concat(&path[0]);
	while (path[++i])
	{
		status = bltn_cd_loop(path[i], env, fl);
		if (status != 0)
			break ;
	}
	return (bltn_cd_argrec_ret(&path, status, env));
}
