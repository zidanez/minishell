/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 13:55:49 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/04 18:25:32 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		bltn_exit(char **args, t_env *env)
{
	int res;

	if (bltn_cd_countargs(args) == 1)
	{
		et_rm_clear_env(env);
		exit(1);
	}
	else if (bltn_cd_countargs(args) == 2)
	{
		res = ft_atoi(args[1]);
		et_rm_clear_env(env);
		exit((unsigned char)res);
		return (res);
	}
	else
		ft_putendl_fd("minishell : exit : too many arguments", 2);
	return (0);
}
