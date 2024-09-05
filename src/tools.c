/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcaratti <vcaratti@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:56:14 by vcaratti          #+#    #+#             */
/*   Updated: 2024/07/15 13:25:25 by vcaratti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_cmds_e_ret(t_cmd *in, t_cmd *out, int error)
{
	int		i;

	if (in->path != NULL)
		free(in->path);
	if (in->args != NULL)
	{
		i = 0;
		while (in->args[i])
			free(in->args[i++]);
		free(in->args);
	}
	if (out->path != NULL)
		free(out->path);
	if (out->args != NULL)
	{
		i = 0;
		while (out->args[i])
			free(out->args[i++]);
		free(out->args);
	}
	return (error);
}

int	free_map_e_ret(char **arr, int error)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	return (error);
}

void	close_wait(int *fd, int *children, int *files)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(children[0], NULL, 0);
	waitpid(children[1], NULL, 0);
	close(files[0]);
	close(files[1]);
}

void	close_2(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	open_files(char *infile, char *outfile, int *file_fds)
{
	file_fds[0] = open(infile, O_RDONLY);
	if (file_fds[0] == -1)
		perror(NULL);
	file_fds[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_fds[1] == -1)
		perror(NULL);
	if (file_fds[0] < 0 && file_fds[1] < 0)
		return (-1);
	if (file_fds[0] < 0 && file_fds[1] >= 0)
		return (close(file_fds[1]), -1);
	if (file_fds[1] < 0 && file_fds[0] >= 0)
		return (close(file_fds[0]), -1);
	return (0);
}
