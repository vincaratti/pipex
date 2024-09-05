/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:40:27 by vcaratti          #+#    #+#             */
/*   Updated: 2024/07/15 17:29:48 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_child_cmd
{
	int		child;
	t_cmd	cmd;
	int		*fd;
	int		*files;
	char	**envp;
}	t_child_cmd;

// cmd_path.c //
int		cmd_path(char *cmd, char **envp, char **ret);

// init_cmds.c //
int		init_cmds(t_cmd *in, t_cmd *out);

// tools.c //
int		free_cmds_e_ret(t_cmd *in, t_cmd *out, int error);
int		free_map_e_ret(char **arr, int error);
void	close_wait(int *fd, int *children, int *files);
void	close_2(int *fd);
int		open_files(char *infile, char *outfile, int *file_fds);

// children.c //
int		child_in(t_cmd cmds, int *fd, int *files, char **envp);
int		child_out(t_cmd cmds, int *fd, int *files, char **envp);
int		run_child_in(t_child_cmd c);
int		run_child_out(t_child_cmd c);
#endif
