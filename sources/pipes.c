
#include <stdlib.h>
#include <math.h>

#include "pipes.h"
#include "solution.h"

/*
** Créer un nouveau pipe, un pipe relie deux villes
*/
pipe_t* pipe_create(city_t* left, city_t* right)
{
	pipe_t* ret = malloc(sizeof(pipe_t));

	if (ret != NULL)
	{
		ret->left = left;
		ret->right = right;
	}
	return ret;
}

/*
** Détruit un pipe à partir d'un pointeur générique
*/
void pipe_destroy_void(void* pipe)
{
	pipe_destroy((pipe_t*)pipe);
}

/*
** detruit un pipe
*/
void pipe_destroy(pipe_t* pipe)
{
	if (pipe == NULL)
		return;
	free(pipe);
}

/*
** calcul la distance entre deux ville
*/
float pipe_calc_distance(city_t* f, city_t* s)
{
	double w, p = M_PI / 180;
	
	w = 0.5 - cosf((s->latitude - f->latitude) * p) / 2 +
		cosf(f->latitude * p) * cosf(s->latitude * p) *
		(1 - cosf((s->longitude - f->longitude) * p)) / 2;
	w = 12742 * asinf(sqrtf(w)); // 2 * R; R = 6371 km
	return w;
}

/*
** Dit si un pipe est inutile ou non, Un pipe entre
** deux villes du même groupe sont inutiles, car
** ils sont déjà liés
*/
int pipe_is_useless(pipe_t* pipe)
{
	if (pipe == NULL)
		return YES;
	if (pipe->left == NULL || pipe->right == NULL)
		return YES;
	if (pipe->left->group != pipe->right->group)
		return NO;
	return YES;
}

/*
** reLie deux villes, ajoute le pipe dans le tas binaire de solution
** en utilisant la distance entre les deux villes comme poids de noeud
*/
int pipe_two_cities(solution_t* s, city_t* first, city_t* second)
{
	float weight;
	pipe_t* pipe;

	if (first == NULL || second == NULL)
		return 1;
	if ((pipe = pipe_create(first, second)) == NULL)
		return 1;
	weight = pipe_calc_distance(first, second);
	bin_heap_append(s->pipes, weight, pipe);
	return 0;
}
