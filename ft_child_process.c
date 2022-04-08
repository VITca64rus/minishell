/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:22:16 by natalia           #+#    #+#             */
/*   Updated: 2022/04/05 22:26:56 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_comand(char **cmd1, char ***comands, \
						char **path, t_pipex **data)
{  
    // printf("Check1\n");
    printf("comands = %s\n", *comands[0]);
	if (access((*comands)[0], 0) == 0)
	{
        printf("Check2\n");
		*path = (*comands)[0];
		*comands = ft_comands_for_full_path(*cmd1, *comands);
	}
	else
	{
        printf("Check3\n");
		*comands = NULL;
		*path = ft_check_sistem_bin(*cmd1, &(*comands), (*data)->paths);
		if (*path == NULL)
		{
			write(1, "pipex: can not find comand: ", 29);
			write(1, *cmd1, ft_strlen(*cmd1));
			write(1, "\n", 1);
			return ;
		}
	}
}

void	child_process(int pipefd[2], char **cmd_args, t_pipex *pipex, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	//comands = cmd_args;
	//comands = ft_split(cmd1, ' ');
	ft_check_comand(&cmd_args[0], &cmd_args, &path, &pipex);
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		perror("pipex");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		perror("pipex");
	close(pipex->infile);
	close(pipefd[0]);
	execve(path, cmd_args, envp);
}
