
#include <stdlib.h>
#include <stdio.h>

#include "binary.h"

/*
** Créer un nouveau tas binaire
*/
bin_heap_t* bin_heap_create()
{
	return bin_heap_create_reserve(HEAP_DEFAULT_SIZE);
}

/*
** Créer un nouveau tas binaire avec une taille spéciale
*/
bin_heap_t* bin_heap_create_reserve(size_t max_size)
{
	bin_heap_t* ret = malloc(sizeof(bin_heap_t));
	size_t slots = MAX(max_size, HEAP_DEFAULT_SIZE);

	if (ret != NULL)
	{
		ret->nodes = malloc(sizeof(bin_node_t) * slots);
		if (ret->nodes == NULL)
			return NULL;
		ret->max_size = slots;
		ret->size = 0;
	}
	return ret;
}

/*
** Détruit un tas binaire
** Détruit le pointeur des noeuds mais pas les éléments qu'il contient
*/
void bin_heap_destroy(bin_heap_t* heap)
{
	if (heap == NULL)
		return;
	if (heap->nodes != NULL)
		free(heap->nodes);
	free(heap);
}

/*
** Détruit un tas binaire
** Détruit le pointeur des noeuds et ses éléments grâce à un destructeur
** fonction donnée en paramètre ou la fonction 'free' par défaut
*/
void bin_heap_destroy_full(bin_heap_t *heap, void (*func)(void*))
{
	if (heap == NULL)
		return;
	if (heap->nodes != NULL)
	{
		for (size_t it = 0; it < heap->size; ++it)
		{
			if (func == NULL)
				free(heap->nodes[it].data);
			else
				func(heap->nodes[it].data);
		}
	}
	bin_heap_destroy(heap);
}
