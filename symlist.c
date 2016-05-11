#include "ft_nm.h"

void	add_to_list(t_list **list, void *data)
{
	t_list		*new_list;
	t_list		*tmp;
	
	new_list = (t_list*)malloc(sizeof(t_list));
	new_list->data = data;
	new_list->next = NULL;
	if (!(*list))
		*list = new_list;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_list;
	}
}