/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 04:21:07 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/03 16:58:45 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void				bltn_cd_parse_flgs(char *str, t_flags *flgs)
{
	int				i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == 'P')
			flgs->first = 1;
		if (str[i] == 'L')
			flgs->first = 0;
	}
}

int					bltn_cd_parser(t_env *env, t_dlist **path)
{
	char			*tmp_str;
	t_dyn_string	*str;
	t_dyn_string	*tmp;

	env = 0;
	str = dstr_new(g_pwd->txt);
	while (str->strlen != 0)
	{
		if (ft_strrchr(str->txt, '/'))
		{
			tmp = dstr_slice_cut(&str, (ft_strrchr(str->txt, '/') - str->txt),\
										str->strlen);
			tmp_str = ft_strsub(tmp->txt, 1, tmp->strlen);
			if (!(*path))
				(*path) = ft_dlstnew(tmp_str, tmp->strlen);
			else if (ft_strlen(tmp_str))
				ft_dlstunshift(&(*path), ft_dlstnew(tmp_str, tmp->strlen));
			dstr_del(&tmp);
			free(tmp_str);
		}
	}
	dstr_del(&str);
	return (1);
}
