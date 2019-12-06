/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:29:19 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:23:36 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			exe_launch(char **argv, t_env *env)
{
	pid_t	pid;
	char	*path;
	char	**en;

	if (exe_parsecmd(argv[0], env, &path))
	{
		en = ft_avl_tree_to_warr(env->globals, &avln_todstring_key_val);
		pid = fork();
		if (pid == 0)
		{
			execve(path, argv, en);
			exit(1);
		}
		else if (pid < 0)
			ft_putendl_fd("minishell : can't fork()", 2);
		else
			waitpid(pid, 0, 0);
		free(path);
		free_spl(&en);
	}
	return (0);
}
