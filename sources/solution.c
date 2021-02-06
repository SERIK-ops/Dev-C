
#include <stdio.h>
#include <stdlib.h>

#include "solution.h"
#include "pipes.h"

/*
** Crée un nouveau noeud de solution et l'ajoute  aux solutions optimales
*/
static int solution_create_node(solution_t* s, pipe_t* pipe, float weight)
{
	sol_node_t* node = malloc(sizeof(sol_node_t));

	if (node == NULL)
		return 1;
	node->weight = weight;
	node->pipe = pipe;
	node->next = NULL;
	if (s->last == NULL)
		s->solution = node;
	else
		s->last->next = node;
	s->last = node;
	return 0;
}

/*
** Lorsqu'un pipe est validé, les villes liées par ce pipe
** sont fusionnés dans le même groupe et la structure de la solution
** stocke le pipe pour la solution optimale
*/
static void	 validate_pipe(solution_t *s, pipe_t *pipe, float weight)
{
	s->countdown -= 1;
	solution_create_node(s, pipe, weight);
	city_merge_grp(s->cities, pipe->left->group, pipe->right->group);
}

/*
** demare l algorithm
*/
int algo(solution_t *s)
{
	pipe_t* pipe;
	float weight;

	while (s->countdown > 0 && (pipe = bin_heap_extract_min(s->pipes, &weight)) != NULL)
	{
		if (pipe_is_useless(pipe) == YES)
		{
			pipe_destroy(pipe);
			continue;
		}
		validate_pipe(s, pipe, weight);
	}
	return 0;
}

/*
** Initialise la structure de la solution
*/
void solution_init(solution_t* solution)
{
	solution->countdown = 0;
	solution->groups = NULL;
	solution->solution = NULL;
	solution->last = NULL;
	solution->cities = NULL;
	solution->pipes = bin_heap_create();
}

/*
** libere la structure de la solution
*/
void solution_end(solution_t* solution)
{
	sol_node_t* node = solution->solution;
	sol_node_t* tmp;

	while (node != NULL)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
	city_grp_destroy_all(solution->groups);
	bin_heap_destroy_full(solution->pipes, &pipe_destroy_void);
}
/*
affiche les villes chargées et la taille de la solution
*/
void solution_dump(solution_t* s)
{
	sol_node_t* node = s->solution;
	pipe_t* pipe;
	float lenght = 0.0;

	while (node != NULL)
	{
		pipe = node->pipe;
		printf("%lu %lu\n", pipe->left->id, pipe->right->id);
		lenght += node->weight;
		node = node->next;
	}
	printf("Total lenght: %f\n", lenght);
}
