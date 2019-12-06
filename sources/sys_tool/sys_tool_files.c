/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_tool_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:33:45 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/05 18:28:25 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys_tool.h"
#include <sys/types.h>
#include <sys/stat.h>

int		sys_file_exist(char *path)
{
	if (!access(path, 0))
		return (1);
	return (0);
}

int		sys_file_type(char *path)
{
	struct stat st;

	if (sys_file_exist(path))
	{
		if (!access(path, 1))
			return (FILE_BIN);
		stat(path, &st);
		if (S_ISDIR(st.st_mode))
			return (FILE_DIR);
		if (S_ISREG(st.st_mode))
			return (FILE_FILE);
	}
	return (0);
}
