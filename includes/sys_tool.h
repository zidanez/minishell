/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_tool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnancy <fnancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:31:56 by fnancy            #+#    #+#             */
/*   Updated: 2019/12/04 14:40:33 by fnancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_TOOL_H
# define SYS_TOOL_H
# define FILE_DIR	1
# define FILE_FILE	2
# define FILE_BIN	3

# include <unistd.h>

int		sys_file_exist(char *path);
int		sys_file_type(char *path);

#endif
