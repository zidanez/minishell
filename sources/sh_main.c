/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:46:26 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:29:09 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	write_dir(void)
{
	ft_putstr("\033[32m -> ");
	ft_putstr(g_pwd->txt);
	ft_putstr(" \033[0m> ");
}

static void	free_g_cd_glob(void)
{
	dstr_del(&g_cd_oldpwd);
	dstr_del(&g_cd_pwd);
}

int			sh_loop(t_env *env)
{
	int		stts;
	char	*line;
	char	**argv;
	char	**ar;
	int		i;

	stts = 0;
	while (!stts)
	{
		write_dir();
		line = read_line();
		argv = ft_tokenizer(line);
		i = -1;
		while (argv[++i])
		{
			ar = ft_strsplits(argv[i], "\t ' '");
			stts = sh_execute(ar, env);
			if (ft_strequ(ar[0], "cd"))
				free_g_cd_glob();
			free_spl(&ar);
		}
		free(line);
		free_spl(&argv);
	}
	return (stts);
}

int			main(int argc, char **argv, char **env)
{
	t_env	en;

	env_init(env, &en);
	return (sh_loop(&en));
}
