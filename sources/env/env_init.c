/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:06:34 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:22:58 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			bltn_count_builtins(void)
{
	return (sizeof(g_bltns_str) / sizeof(char *));
}

static int	bltn_init(t_env *env)
{
	int		i;
	char	path[1024];

	i = -1;
	while (++i < bltn_count_builtins())
	{
		if ((ft_avl_set(env->builtns, ft_avl_node_cc(g_bltns_str[i],\
		g_bltns_func[i], sizeof(g_bltns_func[i])))) == -1)
			return (-1);
	}
	if (getcwd(path, sizeof(path)) == NULL)
		return (-1);
	g_pwd = dstr_new(path);
	g_oldpwd = dstr_new(path);
	return (1);
}

static int	env_init_error(t_env *env, int errcode)
{
	if (errcode == 12)
		et_rm_clear_env(env);
	return (errcode);
}

int			env_init(char **en, t_env *env)
{
	char	**spl;

	spl = NULL;
	if (!(env->globals = ft_avl_tree_create(free))\
		|| !(env->builtns = ft_avl_tree_create(0))\
		|| !(env->cmds = ft_avl_tree_create(free)))
		return (env_init_error(env, 12));
	while (*en)
	{
		spl = ft_strsplit(*en, '=');
		if ((ft_avl_set(env->globals, ft_avl_node(spl[0], (char *)spl[1],\
		spl[1] ? ft_strlen(spl[1]) + 1 : 0)) == -1))
		{
			free_spl(&spl);
			return (env_init_error(env, 12));
		}
		free_spl(&spl);
		en++;
	}
	if (bltn_init(env) == -1)
		return (env_init_error(env, 12));
	return (1);
}
