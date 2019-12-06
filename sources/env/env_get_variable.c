/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:12:12 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/03 17:37:00 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

DSTRING		*env_get_variable(const char *key, t_env *enviroment)
{
	DSTRING	*res;
	t_avln	*node;

	if ((node = ft_avl_search(enviroment->globals, key)) != NULL)
	{
		if (!(res = dstr_new((char *)node->content)))
			res = NULL;
	}
	else
	{
		if (!(res = dstr_new("")))
			res = NULL;
	}
	return (res);
}
