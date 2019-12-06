/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:30:30 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/06 10:54:44 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	setenv_error(char ***str, int errcode)
{
	free_spl(str);
	if (errcode == 1488)
		ft_putendl_fd("minishell : setenv: '=' - bad input", 2);
	return (0);
}

static void	free_spl_here(char **args)
{
	if (args[1])
		free(args[1]);
	if (args[0])
		free(args[0]);
	free(args);
}

int			bltn_setenv(char **args, t_env *env)
{
	t_avln	*node;
	int		i;
	char	**spl;

	i = 0;
	while (args[++i])
	{
		spl = ft_strsplit(args[i], '=');
		if (!spl[0])
			return (setenv_error(&spl, 1488));
		if (!spl[1])
			spl[1] = ft_strdup("");
		else
		{
			if (!(node = ft_avl_node(spl[0], spl[1], ft_strlen(spl[1]) + 1)))
				return (setenv_error(&spl, 210));
			if (ft_avl_set(env->globals, node) == -1)
				return (setenv_error(&spl, 210));
		}
		free_spl_here(spl);
	}
	return (0);
}
