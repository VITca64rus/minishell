#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include "libft/libft.h"

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

#endif