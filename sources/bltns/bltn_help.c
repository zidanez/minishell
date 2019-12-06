/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:31:12 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:22:36 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				bltn_help(char **arg, t_env *env)
{
	int i;

	if (ft_strequ(arg[0], "help") && ft_avl_search(env->builtns, "help")\
		!= NULL)
	{
		ft_putendl("fnancy's MINISHELL");
		ft_putendl("Write program names and arguments, and press enter.");
		ft_putendl("The following commands:");
		i = -1;
		while (++i < bltn_count_builtins())
			ft_putendl(g_bltns_str[i]);
	}
	return (0);
}
