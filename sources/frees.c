/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:12:48 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:27:07 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void			free_spl(char ***spl)
{
	int			i;

	if (!(*spl))
		return ;
	i = -1;
	while ((*spl)[++i])
	{
		if ((*spl)[i])
			free((*spl)[i]);
	}
	free((*spl));
}

void			et_rm_warr(char **args)
{
	size_t		i;

	i = -1;
	while (args[++i])
	{
		free((void *)args[i]);
	}
	free((void *)args);
}

void			et_rm_clear_env(t_env *env)
{
	int		i;
	t_avln	*node;

	i = -1;
	while (++i < bltn_count_builtins())
	{
		node = ft_avl_search(env->builtns, g_bltns_str[i]);
		node->content = NULL;
	}
	if (env->globals)
		ft_avl_tree_free(env->globals);
	if (env->builtns)
		ft_avl_tree_free(env->builtns);
	if (env->cmds)
		ft_avl_tree_free(env->cmds);
	dstr_del(&g_pwd);
	dstr_del(&g_oldpwd);
}
