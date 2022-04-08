/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:55:02 by natalia           #+#    #+#             */
/*   Updated: 2022/04/05 22:25:52 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(int pipefd[2], char **cmd2, t_pipex *pipex, char **envp)
{
	int		status;
	char	*path;

	path = NULL;
    // cmd2[0] = "wc";
    // cmd2[1] = "-l";
	waitpid(pipex->pid, &status, 0);
	ft_check_comand(&cmd2[0], &cmd2, &path, &pipex);
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		perror("pipex");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("pipex");
	close(pipefd[1]);
	close(pipex->outfile);
	execve(path, cmd2, envp);
	//ft_free_arg(comands);
}