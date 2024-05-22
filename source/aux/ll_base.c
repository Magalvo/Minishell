
#include "../include/minishell.h"

/*
base moves, all operations use some sort of combination of these 4
*/

// todo
// add mid
// remove mid

// add node at beggining of list
void	push_node(t_node **first, t_node *node)
{
	if (stack->head == NULL)
	{
		stack->head = node;
		stack->tail = node;
		stack->size++;
		return ;
	}
	node->next = stack->head;
	stack->head->prev = node;
	stack->head = node;
	stack->size++;
}

// add node at end of list
void	append_node(t_header *stack, t_node *node)
{
	if (stack->head == NULL)
	{
		stack->head = node;
		stack->tail = node;
		stack->size++;
		return ;
	}
	stack->tail->next = node;
	node->prev = stack->tail;
	stack->tail->next = node;
	stack->tail = node;
	stack->size++;
}

// extract first node
t_node	*pop_node(t_header *stack)
{
	t_node	*temp;

	temp = stack->head;
	if (stack->head == NULL)
		return (NULL);
	if (temp == stack->tail)
	{
		stack->head = NULL;
		stack->tail = NULL;
	}
	else
	{
		stack->head = stack->head->next;
		stack->head->prev = NULL;
	}
	temp->next = NULL;
	temp->prev = NULL;
	stack->size--;
	return (temp);
}

// extract last node
t_node	*pop_last_node(t_header *stack)
{
	t_node	*last;

	if (stack->head == NULL)
		return (NULL);
	last = stack->tail;
	if (stack->size == 1)
	{
		stack->head = NULL;
		stack->tail = NULL;
	}
	else
	{
		stack->tail = stack->tail->prev;
		stack->tail->next = NULL;
	}
	last->next = NULL;
	last->prev = NULL;
	stack->size--;
	return (last);
}
