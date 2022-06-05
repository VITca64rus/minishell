/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 08:40:01 by natalia           #+#    #+#             */
/*   Updated: 2022/06/03 20:47:38 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_cmd(char *cmd)
{		
	write(2, "pipex: can not find command: ", 29);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(1);
}

void	ft_error_path(char *cmd)
{
	write(2, "pipex: can not find command: ", 29);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(1);
}

char	*ft_check_sistem_bin(char *cmd, char **commands, t_prompt *data)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	commands = ft_split(cmd, ' ');
	while (data->paths[i])
	{
		path = ft_strjoin(data->paths[i], (commands)[0]);
		if (!path)
			exit(0);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (path);
}

char	**ft_comands_for_full_path(char *cmd, char **comands)
{
	int		i;

	i = 0;
	comands = ft_split(cmd, '/');
	if (!comands)
	{
		free(comands);
	}
	while (comands[i])
	{
		i++;
	}
	i--;
	comands = ft_split((comands)[i], ' ');
	return (comands);
}

void	ft_check_command(char **commands, t_prompt *data, char **envp)
{
	char	*path;
	int		res;


	if (access(commands[0], 0) == 0)
	{
		path = commands[0];
		commands = ft_comands_for_full_path(commands[0], commands);
	}
	else
		path = ft_check_sistem_bin(commands[0], commands, data);
	if (path == NULL)
		ft_error_path(commands[0]);
	res = execve(path, commands, envp);
	if (res == -1)
		ft_error_cmd(commands[0]);
}

void	ft_error_pid(void)
{
	perror("pid error");
	exit(1);
}

void	first_comm_proccess(t_prompt *data, char **commands, char **envp, int fd)
{
	int		pipefd[2];

	pipe(pipefd);
	data->pid = fork();
	if (data->pid == -1)
		ft_error_pid();
	if (data->pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		if (fd == 0)
			exit(1);
		else
			ft_check_command(commands, data, envp);
	}
}

int	ft_open_fd(char *file1, t_prompt *pipex, int flag)
{
	if (flag == 1)
	{
		pipex->infile = open(".here_doc", O_CREAT | O_RDWR | O_APPEND, 0777);
		dup2(pipex->infile, 1);
	}
	if (flag == 0)
	{
		pipex->infile = open(file1, O_RDONLY, 0777);
		//pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(pipex->infile, 0);
		//dup2(data->outfile, 1);
	}
	// if (data->outfile < 0 || data->infile < 0)
	// {
	// 	perror("pipex");
	// 	free(data);
	// 	return (1);
	// }
	return (0);
}

int	ft_check_path(t_prompt *data)
{
	if (data->paths == NULL)
	{
		write(1, "pipex: PATH not found\n", 23);
		free(data);
		return (1);
	}
	return (0);
}

char	*ft_find_path_in_envp(char **envp)
{
	char	*path_envp;

	path_envp = NULL;
	while (envp != 0)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			path_envp = *(envp);
			path_envp = &path_envp[5];
			break ;
		}
		envp++;
	}
	return (path_envp);
}

char	**ft_find_path(char **envp)
{
	char	*path_envp;
	char	**paths;
	char	*tmp;
	int		i;

	path_envp = NULL;
	paths = NULL;
	i = 0;
	path_envp = ft_find_path_in_envp(envp);
	if (path_envp == NULL)
		return (NULL);
	paths = ft_split(path_envp, ':');
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}

int	ft_pipex(t_data *data, t_info *info, char **envp)
{
	t_prompt	*pipex;
	int		i;

	pipex = (t_prompt *)malloc(sizeof(t_prompt));
	pipex->paths = ft_find_path(envp);
	pipex->here_doc = 0;
	if (ft_check_path(pipex))
		return (1);
	while(data)
	{
		if (ft_strncmp(data->type, "<<", 2) == 0) // проверить нужна ли длина, можно ли сломать && ft_strlen(argv[1]) == 8)
		{
			pipex->here_doc = 1;
			pipex->infile = open(".here_doc", O_CREAT | O_RDWR | O_APPEND, 0777);
			dup2(pipex->infile, 1); //написать проверку на неправильное открытие
		}
		if (ft_strncmp(data->type, "<", 1) == 0)
		{
			if (ft_open_fd(data->args[0], pipex, pipex->here_doc)) //открыть в конце outfile
				return (1); 
		}
		if (ft_strncmp(data->type, "COMMAND", 7) == 0 && ft_strncmp(data->next->type, "|", 1) == 0)
		{
			first_comm_proccess(pipex, data->args, envp, 1); // команда приходит уже поделенная
		}
		if (ft_strncmp(data->type, "COMMAND", 7) == 0 && ft_strncmp(data->next->type, ">", 1) == 0)
		{
			pipex->outfile = open(data->next->args[0], O_CREAT | O_RDWR | O_TRUNC, 0777);
			dup2(pipex->outfile, 1);
			ft_check_command(data->args, pipex, envp);
			//data = data->next;
		}
		if (ft_strncmp(data->type, ">", 1) == 0)
		{
			printf("Check\n");
		}
		data = data->next;
		// while (info->num_command - 1)
		// {
			
		// }
		
	}
	// i = 2;
	// if (pipex->here_doc == 1)
	// 	ft_heredoc(argc, argv, pipex, &i);
	// first_comm_proccess(pipex, argv[i], envp, pipex->infile);
	// while (i < argc - 2)
	// 	first_comm_proccess(pipex, argv[i++], envp, 1);
	// ft_check_command(argv[i], pipex, envp);
	// ft_check_pid_status(pipex);
	// free(pipex);
	// exit(0);
	return(0);
}