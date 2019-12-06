/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_unsetenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:30:50 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 12:36:36 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				bltn_unsetenv(char **arg, t_env *env)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (arg[++i])
	{
		if (ft_avl_search(env->globals, arg[i]) != 0)
		{
			if ((ft_avl_del(env->globals, arg[i])) == -1)
				return (0);
			ret = 0;
		}
	}
	return (ret);
}
