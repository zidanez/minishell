/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:43:17 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:26:03 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void			home_concat(char **str, t_env *env)
{
	char			*tmp;
	t_dyn_string	*st;

	st = env_get_variable("HOME", env);
	tmp = ft_strsub((*str), 1, ft_strlen(*str));
	free((*str));
	(*str) = ft_strjoin(st->txt, tmp);
	free(tmp);
	dstr_del(&st);
}

static void			sh_parsetidol(char ***argv, t_env *env)
{
	int				i;
	char			*tmp;
	t_dyn_string	*st;

	i = 0;
	while ((*argv)[++i])
	{
		if ((*argv)[i][0] == '$')
		{
			tmp = ft_strsub((*argv)[i], 1, ft_strlen((*argv)[i]));
			st = env_get_variable(tmp, env);
			free(tmp);
			free((*argv)[i]);
			((*argv)[i]) = ft_strdup(st->txt);
			dstr_del(&st);
		}
		else if ((*argv)[i][0] == '~')
			home_concat(&(*argv)[i], env);
	}
}

int					sh_execute(char **argv, t_env *env)
{
	int				i;
	int				(*func)(char **, t_env *);

	i = -1;
	if (!argv || argv[0] == NULL)
		return (0);
	sh_parsetidol(&argv, env);
	if (ft_avl_search(env->builtns, argv[0]))
	{
		func = ft_avl_search(env->builtns, argv[0])->content;
		return (func(argv, env));
	}
	return (exe_launch(argv, env));
}
