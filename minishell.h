#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

# define GREAT	1
# define LESS	2
# define GREATGREAT 3
# define LESSLESS 4
# define GREATAMPERSAND 5
# define PIPE 6
# define AMPERSAND 7
# define NOTOKEN 8

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

typedef struct s_info
{
	int		num_command;
	int		num_type;
	int		num_builtins;
}	t_info;

//----pipex---

typedef struct s_prompt
{
	char	**paths;
	int		infile;
	int		outfile;
	pid_t	pid;
	int		here_doc;
}				t_prompt;


void	ft_lstadd_back(t_tokens **lst, t_tokens *new);
t_data	*ft_parse(char *str);
void	ft_lstadd_back1(t_data **lst, t_data *new);
void	lexical_analyzer(t_data *data, t_info *info);
int		ft_pipex(t_data *data, t_info *info, char **envp);
void	echo(t_data el);

#endif