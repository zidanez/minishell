/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:30:01 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/03 15:50:06 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				bltn_env(char **arg, t_env *env)
{
	char	**mas;
	int		i;

	if (!env->globals)
		return (210);
	if (bltn_cd_countargs(arg) > 1)
		bltn_setenv(arg, env);
	i = -1;
	if (!(mas = ft_avl_tree_to_warr(env->globals, &avln_todstring_key_val)))
		return (210);
	while (mas[++i])
		ft_putendl(mas[i]);
	et_rm_warr(mas);
	return (0);
}
