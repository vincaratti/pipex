/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:05:03 by vcaratti          #+#    #+#             */
/*   Updated: 2024/07/15 17:28:27 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_in(t_cmd cmds, int *fd, int *files, char **envp)
{
	close(fd[0]);
	if (dup2(files[0], 0) == -1)
		return (close(files[0]), close(fd[1]), -1);
	close(files[0]);
	if (dup2(fd[1], 1) == -1)
		return (close(fd[1]), -1);
	close(fd[1]);
	execve(cmds.path, cmds.args, envp);
	return (0);
}

int	child_out(t_cmd cmds, int *fd, int *files, char **envp)
{
	close(fd[1]);
	if (dup2(fd[0], 0) == -1)
		return (close(files[1]), close(fd[0]), -1);
	if (dup2(files[1], 1) == -1)
		return (close(files[1]), close(fd[0]), -1);
	close(files[1]);
	close(fd[0]);
	execve(cmds.path, cmds.args, envp);
	return (0);
}

int	run_child_in(t_child_cmd c)
{
	if (c.child == 0)
	{
		if (child_in(c.cmd, c.fd, c.files, c.envp) < 0)
			return (-1);
	}
	return (0);
}

int	run_child_out(t_child_cmd c)
{
	if (c.child == 0)
	{
		if (child_out(c.cmd, c.fd, c.files, c.envp) < 0)
			return (-1);
	}
	return (0);
}
