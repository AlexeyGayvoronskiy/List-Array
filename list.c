#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define LISTOBJ(l) (ListObject *) ((char *)l + sizeof(List))

ContainerMethods ListMethods = {
	listInsertFirst,
	listInsertLast,
	listDeleteLast,
	listForeach,
	listSize,
	listDestroy,
	listFirst,
	listLast,
	listGet
};
//Типчики и структурки 
typedef struct ListElement 
{
	void * prev;
	void * data;
	void * next;
} ListElement;

typedef struct ListObject 
{
	int size;
	ListElement * head;
	ListElement * tail;
} ListObject;

//Методы итератора

Iterator listIteratorFirst(List * l) 
{
	Iterator iter;
	ListObject * lo = LISTOBJ(l);
	iter.li.pos = lo->head;
	return iter;
};
Iterator listIteratorLast(List * l) 
{
	Iterator iter;
	ListObject * lo = LISTOBJ(l);
	iter.li.pos = lo->tail;
    return iter;
};

int listIteratorEquals(Iterator a, Iterator b) 
{
	ListElement * one = a.li.pos;
	ListElement * two = b.li.pos;
	if (one->data == two->data)
		return 1;
	else
		return 0;
};

Iterator listIteratorNext(Iterator li) 
{
	Iterator res;
	ListElement * le = malloc(sizeof(ListElement));

	le = li.li.pos;

	if (le != NULL) 
	{
		if (le->next != NULL) 
		{
			res.li.pos = le->next;
			return res;
		}
		else
			exit(-1);
	}
	else
		exit(-1);
};
Iterator listIteratorPrev(Iterator li) 
{
	Iterator res;
	ListElement * le = malloc(sizeof(ListElement));
	le = li.li.pos;
	if (le != NULL) 
	{
		if (le->prev != NULL) 
		{
			res.li.pos = le->prev;
			return res;
		}
		else
			exit(-1);
	}
	else
		exit(-1);
};
void * listIteratorGet(Iterator li) 
{
	ListElement * a = li.li.pos;
	return a->data;
};

//Методы листа

List * listCreate() 
{
	List * l = malloc(sizeof(List) + sizeof(ListObject));
	l->m = &ListMethods;
	ListObject * p = LISTOBJ(l);
	p->head = NULL;
	p->tail = NULL;
	p->size = 0;
	return l;
};
void listInsertFirst(List * l, void * data) 
{
	ListObject * lo = LISTOBJ(l);
	ListElement * old = lo->head;
	ListElement * head = malloc(sizeof(ListElement));

	head->prev = NULL;
    head->data = data;
    head->next = old;

    if (old != NULL) 
	{
	    old->prev = head;
	}

	lo->head = head;
	lo->size++;

	if (lo->size == 1)
		lo->tail = head;
};
void listInsertLast(List * l, void * data) 
{
	ListObject * lo = LISTOBJ(l);
	ListElement * tail = malloc(sizeof(ListElement));
	ListElement * last = lo->tail;

	tail->prev = NULL;
	tail->data = data;
	tail->next = NULL;

	if (last != NULL) 
	{
		tail->prev = last;
	    last->next = tail;
    }

    lo->tail = tail;
    lo->size++;

    if (lo->size == 1)
		lo->head = tail;
};
void * listDeleteLast(List * l) 
{
	ListObject * lo = LISTOBJ(l);
	ListElement * last = lo->tail;

	if (lo->size == 0)
    	return NULL;

	ListElement * pre = last->prev;
    void * x;

    x = last->data;

    if (lo->size > 1) 
	{
	    free(last);
	    pre->next = NULL;
	    lo->tail = pre;
	}
	else 
	{
		free(last);
		lo->tail = NULL;
		lo->head = NULL;
	}

	lo->size--;
    return x;
};
void listForeach(List * l, void (* func)(void * data, void * funcarg), void * arg) 
{
	Iterator first = l->m->first(l);
	Iterator last = l->m->last(l);
	Iterator iter = first;

	do 
	{
		ListElement * le = iter.li.pos;
		void * data = le->data;

		func(data, arg);

		iter = listIteratorNext(iter);
	} while (listIteratorEquals(iter, last));
};
int listSize(List * l) 
{
	ListObject * lo = LISTOBJ(l);
	return lo->size;
};
void listDestroy(List * l) 
{
	while (listSize(l) > 0) 
	{
        listDeleteLast(l);
    }

	free(l);
};
Iterator listFirst(List * l) 
{
	return listIteratorFirst(l);
};
Iterator listLast(List * l) 
{
	return listIteratorLast(l);
};
void * listGet(Iterator li) 
{
	return listIteratorGet(li);
};