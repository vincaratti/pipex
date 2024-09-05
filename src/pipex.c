/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:54:03 by vcaratti          #+#    #+#             */
/*   Updated: 2024/07/15 17:35:50 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	treat_cmd(char *cmd, char **envp, t_cmd *ret)
{
	int	path_return;

	ret->args = ft_split(cmd, ' ');
	if (ret->args == NULL || ret->args[0] == NULL)
		return (-1);
	path_return = cmd_path(ret->args[0], envp, &(ret->path));
	if (path_return == -1)
		return (-1);
	if (path_return == -2)
	{
		write(2, "Command not found\n", 18);
		return (-1);
	}
	return (0);
}

static int	start_fork(int *childfd)
{
	*childfd = fork();
	return (*childfd);
}

static int	run(char **argv, char **envp)
{
	int		fd[2];
	int		files[2];
	int		children[2];
	t_cmd	cmd_in;
	t_cmd	cmd_out;

	if (open_files(argv[1], argv[4], files) < 0 && init_cmds(&cmd_in, &cmd_out))
		return (-1);
	if ((treat_cmd(argv[2], envp, &cmd_in) < 0
			|| treat_cmd(argv[3], envp, &cmd_out) < 0) || pipe(fd) == -1)
		return (close_2(files), free_cmds_e_ret(&cmd_in, &cmd_out, 1));
	if (start_fork(&children[0]) == -1)
		return (close_2(files), free_cmds_e_ret(&cmd_in, &cmd_out, 1));
	if (run_child_in((t_child_cmd){children[0], cmd_in, fd, files, envp}) < 0)
		return (close_2(files), free_cmds_e_ret(&cmd_in, &cmd_out, 1));
	if (start_fork(&children[1]) == -1)
		return (close_2(files), free_cmds_e_ret(&cmd_in, &cmd_out, 1));
	if (run_child_out((t_child_cmd){children[1], cmd_out, fd, files, envp}) < 0)
		return (waitpid(children[1], NULL, 0), close_2(files),
			free_cmds_e_ret(&cmd_in, &cmd_out, 1));
	close_wait(fd, children, files);
	return (free_cmds_e_ret(&cmd_in, &cmd_out, 0));
}

int	main(int argc, char **argv, char **envp)
{
	int	ret;

	if (argc != 5)
		return (write(2, "Wrong number of arguments\n", 26), -1);
	ret = run(argv, envp);
	return (ret);
}
//system("leaks pipex");
