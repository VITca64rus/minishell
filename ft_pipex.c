/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:09:29 by natalia           #+#    #+#             */
/*   Updated: 2022/04/05 22:31:42 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_path_in_envp(char **envp)
{
	while (envp != 0)
	{
		if (!ft_strncmp("PATH=", *envp, 5))
			return (&(*envp[5]));
		envp++;
	}
    return (NULL);
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
		free (tmp);
		i++;
	}
	return (paths);
}

int	ft_check_path(t_pipex *data)
{
	if (data->paths == NULL)
	{
		write(1, "pipex: PATH not found\n", 23);
		free(data);
		return (1);
	}
	return (0);
}

int ft_open_fd(t_data *data, t_pipex *pipex)
{
	while (data)
    {
        if (!strcmp(data->type, "<"))
        {
            pipex->infile = open(data->args[0], O_RDONLY, 0777);
            //printf("%d\n", pipex->infile);
            if (pipex->infile == -1)
            {
                perror("pipex: error open");
                free(pipex);
                return(1);
            }
                
        }
        if (!strcmp(data->type, ">"))
        {
            pipex->outfile = open( data->args[0], O_CREAT | O_RDWR | O_TRUNC, 0777);
            if (pipex->outfile == -1)
            {
                perror("pipex: error open");
                free(pipex);
                return(1);
            }
        }
        data = data->next;
    }
	return (0);
}

void    ft_handle_last(int *pipefd, char **cmd2, t_pipex *pipex, char **envp)
{
    int		status;
	char	*path;
    char **comands;

	path = NULL;
	waitpid(pipex->pid, &status, 0);
    printf("outfile = %d\n", pipex->outfile);
	ft_check_comand(&cmd2[0], &cmd2, &path, &pipex);
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		perror("pipex");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("pipex");
	close(pipefd[1]);
	close(pipex->outfile);
	execve(path, cmd2, envp);
}

void    ft_parse_command(int count_cmd, t_pipex *pipex, t_data *data, char **envp, int *pipefd, t_info *store)
{
    if (count_cmd == 0)
    {
        printf("first process\n");
        child_process(pipefd, data->args, pipex, envp);
    }
    else if (count_cmd == (store->command - 1))
    {
        printf("second process\n");
        ft_handle_last(pipefd, data->args, pipex, envp);
    }
    // else
    //     ft_handle_standart()
}

int		ft_pipex(t_info *store, char *here_doc_name, t_data *data, char **envp)
{
    int     pipefd[2];
    int     count_cmd;
    int     i;
    int     status;

    count_cmd = 0;
    t_pipex *pipex;
    pipex = (t_pipex *)malloc(sizeof(t_pipex));
    pipex->paths = ft_find_path(envp);
    if (ft_check_path(pipex))
		return (1);
    if (ft_open_fd(data, pipex))
        return (1);
    pipe(pipefd);
    while (count_cmd < store->pipe)
    {
        while (data)
        {
            if (!strcmp(data->type, "COMMAND"))
            {
                pipex->pid = fork();
                if (pipex->pid == -1)
                    perror("Unable to create pid");
                if (pipex->pid == 0)
                    ft_parse_command(count_cmd, pipex, data, envp, pipefd, store);    
                count_cmd++;
            }
            data = data->next;
        }
    }
    i = 0;
	while (i < count_cmd)
	{
		wait(&status);
        printf("wait\n");
        i++;
		// if (status != 0)
		// 	ft_check_child_status(status);
		// i++;
	}
	//ft_free_arg(pipex->paths);
    return(0);
}

void	ft_init_store(t_data *data, t_info *store)
{
	int i;
	while (data)
	{
		if (!strcmp(data->type, "<<")) //написать свою strcmp
			store->here_doc += 1;
		if (!strcmp(data->type, "COMMAND"))
			store->command += 1;
		if (!strcmp(data->type, "|"))
			store->pipe += 1;
		data = data->next;
	}
	
}
void	ft_creating_procces(t_data *data, char **envp)
{
	int i;
	char *here_doc_name;
	
	t_info *store;
	store = (t_info *)malloc(sizeof(t_info));
	i = 0;
	ft_init_store(data, store);
	ft_pipex(store, here_doc_name, data, envp);
}

// int main(int argc, char **argv, char **envp)
// {
//     char *str;
// 	t_data *data;
// 	str = ft_strdup("< infile.txt cat | wc -l > outfile.txt");
// 	//str = ft_strdup("<< infile ls -l > file| echo 'pine | echo apple'");
// 	data = ft_parsing(str);
// 	ft_creating_procces(data, envp);
// 	//printf("STR = %s\n", str);
// }