#include "container.h"

#ifdef __cplusplus
extern "C" {
#endif

//���� � ����������

typedef struct List 
{
	ContainerMethods * m;
} List;

//������ ���������

Iterator listIteratorFirst(List * l);
Iterator listIteratorLast(List * l);
int listIteratorEquals(Iterator a, Iterator b);
Iterator listIteratorNext(Iterator li);
Iterator listIteratorPrev(Iterator li);
void * listIteratorGet(Iterator li);


//������ ����� 
List * listCreate();
void listInsertFirst(List * l, void * data);
void listInsertLast(List * l, void * data);
void * listDeleteLast(List * l);
void listForeach(List * l, void (* func)(void * data, void * funcarg), void * arg);
int listSize(List * l);
void listDestroy(List * l);
Iterator listFirst(List * l);
Iterator listLast(List * l);
void * listGet(Iterator li);

#ifdef __cplusplus
}
#endif