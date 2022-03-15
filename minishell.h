#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_data
{
	char			**comands;
	struct s_data	*next;
}	t_data;

void	ft_lstadd_back(t_data **lst, t_data *new);
t_data	*ft_parse(char *str);

#endif