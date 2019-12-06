/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:28:39 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:06:13 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				bltn_echo(char **arg, t_env *env)
{
	int			i;

	if (bltn_cd_countargs(arg) == 1)
		ft_putendl("");
	else
	{
		i = 0;
		while (arg[++i])
		{
			ft_putstr(arg[i]);
			if (i != bltn_cd_countargs(arg))
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	return (0);
}
