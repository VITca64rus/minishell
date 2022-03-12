#include "minishell.h"

t_data	*ft_lstlast(t_data *lst)
{
	t_data	*last;

	last = lst;
	while (last && last->next)
		last = last->next;
	return (last);
}


void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*end;

	if (!*lst)
		*lst = new;
	else
	{
		end = ft_lstlast(*lst);
		end->next = new;
	}
}
