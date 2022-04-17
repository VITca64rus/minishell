#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_tokens
{
	char			*str;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_data
{
	char			*type;
	char			**args;
	struct s_data	*next;
}	t_data;

typedef struct	s_info
{
	int	here_doc;
	int	command;
	int	pipe;
}				t_info;

	typedef struct s_pipex
{
	char	**paths;
	int		infile;
	int		outfile;
	pid_t	pid;
}				t_pipex;

typedef struct s_redirs
{
	char *filename;
	int mode;
} t_redirs;

typedef struct s_comnds
{
	t_redirs	**redirs;
	t_list		*args;
	//t_envars 	*envs;
} t_comnds;

// command parser

void	ft_lstadd_back(t_tokens **lst, t_tokens *new);
t_data	*ft_parse(char *str);
void	ft_lstadd_back1(t_data **lst, t_data *new);
int		ft_pipex(t_info *store, char *here_doc_name, t_data *data, char **envp);
void	child_process(int pipefd[2], char **cmd_args, t_pipex *data, char **envp);
char	*ft_check_sistem_bin(char *cmd, char ***comands, char **paths);
char	**ft_comands_for_full_path(char *cmd, char **comands);
void	parent_process(int pipefd[2], char **cmd2, t_pipex *data, char **envp);
void	ft_check_comand(char **cmd1, char ***comands, \
						char **path, t_pipex **data);
t_comnds	**ft_search_command(t_data *data, char **envp);
void	execute_bin(t_data *data, char **comands, char **envp);
int		ft_pipes_redirects(t_data *data);
void	execute_command(t_data *data, char **commands, char **envp);

#endif