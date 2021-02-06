
#include <stdio.h>
#include <stdlib.h>

#include "binary.h"

/*
** Swap le contenu de deux noeuds
*/
static void swap_content(bin_node_t *arr, size_t first, size_t second)
{
	float tmp_w = arr[first].weight;
	void* tmp_d = arr[first].data;
	
	arr[first].weight = arr[second].weight;
	arr[first].data = arr[second].data;
	arr[second].weight = tmp_w;
	arr[second].data = tmp_d;
}

/*
** Organise le tas (un noeud est toujours plus grand que son parent) du bas vers le haut
*/
static void arrange_bottom_up(bin_heap_t* h)
{
	size_t idx = h->size - 1;
	size_t parent;

	while (idx != 0)
	{
		parent = (idx - 1) / 2;
		if (h->nodes[parent].weight < h->nodes[idx].weight)
			break;
		swap_content(h->nodes, idx, parent);
		idx = parent;
	}
}

/*
**Récupère les enfants d'un noeud qui ne respecte pas la règle 
**(un noeud est toujours plus grand que son parent) Si les deux enfants 
**ne respectent pas la règle, le plus petit est retourné
*/
static size_t get_children_to_arrange(bin_node_t* arr, size_t parent, size_t end)
{
	float p_weight = arr[parent].weight;
	float l_weight, r_weight;
	size_t l_idx, r_idx;

	l_idx = parent * 2 + 1; // Définir l'ID de l'enfant gauche
	//s il n y a pas d enfant  gauche on arrete  le swap
	if (l_idx >= end)
		return 0;
	l_weight = arr[l_idx].weight;
	r_idx = l_idx + 1; //  Définir l'ID de l'enfant  droite 
	// S il n y a pas d enfant droit, vérifie uniquement l enfant gauche
	if (r_idx >= end)
		return (p_weight <= l_weight) ? (0) : (l_idx);
	r_weight = arr[r_idx].weight;
	// S il n y a pas d enfant droit, vérifie uniquement l enfant gauche
	if (p_weight <= l_weight && p_weight <= r_weight)
		return 0;
	// Sinon,  renvoie lidentifiant de poids le plus petit
	return (l_weight <= r_weight) ? (l_idx) : (r_idx);
}

/*
**Organise le tas (un noeud est toujours plus grand que son parent) du 
**haut vers le bas
*/
static void arrange_top_down(bin_heap_t* h)
{
	size_t end = h->size - 1;
	size_t idx = 0;
	size_t new_idx;

	while (idx < end)
	{
		new_idx = get_children_to_arrange(h->nodes, idx, end);
		if (new_idx == 0)
			break;
		swap_content(h->nodes, idx, new_idx);
		idx = new_idx;
	}
}

/*
** Ajoute un nouvel élément dans un tas binaire
*/
int bin_heap_append(bin_heap_t* heap, float weight, void* data)
{
	bin_node_t node;

	if (heap == NULL)
		return 1;
	node.weight = weight;
	node.data = data;
	return bin_heap_append_from_node(heap, &node);
}

/*
** Ajoute un nouveau noeud dans un tas binaire
*/
int bin_heap_append_from_node(bin_heap_t* heap, const bin_node_t* node)
{
	if (heap == NULL || node == NULL)
		return 1;
	if (heap->size >= heap->max_size - 1)
	{
		heap->nodes = realloc(heap->nodes, sizeof(bin_node_t) * heap->max_size * 2);
		if (heap->nodes == NULL)
			return 1;
		heap->max_size *= 2;
	}
	heap->nodes[heap->size++] = *node;
	arrange_bottom_up(heap);
	return 0;
}

/*
**Extrait lélément minimum d un tas binaire 
*/
void* bin_heap_extract_min(bin_heap_t* heap, float *weight)
{
	void* ret = NULL;

	if (heap == NULL || heap->size == 0)
		return NULL;
	ret = heap->nodes[0].data;
	if (weight != NULL)
		*weight = heap->nodes[0].weight;
	swap_content(heap->nodes, 0, --heap->size);
	if (heap->size > 0)
		arrange_top_down(heap);
	return ret;
}
