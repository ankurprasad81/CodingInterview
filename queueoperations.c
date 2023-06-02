/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define OK (0)
#define ERROR (-1)
#define QUEUESIZE (32)

typedef struct node_
{
    struct node_* next;
    struct node_* prev;
}node;

typedef struct queue_{
    node* head;
    node* tail;
    size_t count;
}queue;

struct data_struct
{
    node nodeelement;
    int value;
};
int queue_init(queue* qptr);
int queue_add_tail(queue* ptr, node* nodeptr);
int queue_add_head(queue* ptr , node* nodeptr);
int queue_del_head(queue*ptr);
int queue_del_tail(queue* ptr);
int queue_delete(queue* ptr);
int queue_nodecount(queue* q);
int queue_print(queue* ptr);
unsigned int queue_isempty(queue* ptr);
unsigned int queue_isfull(queue*ptr);

static int addData(struct data_struct** d, int val);
static queue q;
int main()
{   
    struct data_struct* data= NULL;
    /*initialize queue*/
    queue_init(&q);
    /*add element to queue */
    addData(&data,4);
    queue_add_head(&q, &data->nodeelement);
    queue_print(&q);
    /*adding node to queue tail */
    addData(&data,5);
    queue_add_head(&q, &data->nodeelement);
    queue_print(&q);
    /*adding data to head*/
    addData(&data, 10);
    queue_add_head(&q, &data->nodeelement);
    queue_print(&q);
     /*adding data to head*/
    addData(&data, 40);
    queue_add_head(&q, &data->nodeelement);
    queue_print(&q);
    /*adding data to tail*/
    addData(&data, 400);
    queue_add_tail(&q, &data->nodeelement);
    queue_print(&q);
    #if 0
    /*delete from head */
    queue_del_head(&q);
    queue_print(&q);
    queue_del_head(&q);
    queue_print(&q);
    /*delete from tail*/
    queue_del_tail(&q);
    queue_print(&q);
    queue_del_tail(&q);
    #endif
    queue_delete(&q);
    queue_print(&q);
    return 0;
}

/************************************************
 * Initializes the queue
 * *********************************************/
int queue_init(queue* queueptr)
{
    /*Ensure queueptr is not null*/
    assert(queueptr!=NULL);
    /* no nodes available */
    queueptr->count = 0;
    /*Head and Tail are NULL */
    queueptr->head = NULL;
    queueptr->tail = NULL;
    return OK;
    
}
/************************************************
 * Adds the node to tail of queue
 * *********************************************/
int queue_add_tail(queue* qptr , node* nodeptr)
{
    
    node* prevtail  = NULL;
    assert(qptr!=NULL);
    assert(nodeptr!=NULL);
    /*check if queue empty */
    if((qptr->count  == 0 ) || (qptr->head == NULL) || (qptr->head == qptr->tail))
    {
        qptr->head = qptr->tail = nodeptr;
    }
    /*queue has not reached the limit */
    else if(qptr->count%QUEUESIZE !=0)
    {
        prevtail = qptr->tail;
        prevtail->next = nodeptr;
        nodeptr->prev = prevtail;
        qptr->tail  = nodeptr;
    }
    
    /*incrmement te count */
    qptr->count++;
    return OK;
    
}
/************************************************
 * adds the node to head of queue
 ***********************************************/
int queue_add_head(queue* qptr , node* nodeptr)
{
    
    node* prevHead  = NULL;
    assert(qptr!=NULL);
    assert(nodeptr!=NULL);
    /*is queue empty*/
    if(qptr->head == NULL)
    {
       qptr->tail = qptr->head = nodeptr;
    }
    else
    {
        prevHead = qptr->head;
        nodeptr->next = prevHead;
        prevHead->prev = nodeptr;
        qptr->head = nodeptr;
    }
    /*incrmement te count */
    qptr->count++;
    return OK;
    
}
/************************************************
 * Print the queue
 * *********************************************/

int queue_print(queue* ptr)
{
    assert(ptr!=NULL);
    node* temp =NULL;
    unsigned int i;
    
    printf("\nNodecount:%lu\n", ptr->count);
    for(temp=ptr->head ; temp!=NULL; temp= temp->next)
    {
        printf("%d-->", ((struct data_struct*)temp)->value);
    }
    printf("NULL");
    
    return OK;
}

/************************************************
 * Print the queue count
 ***********************************************/
    
int queue_nodecount(queue* ptr)
{
    return ptr->count;
}

/************************************************
 * deletes the node from head
 ***********************************************/
int queue_del_head(queue*ptr)
{
    node* headNext =NULL;
    if((ptr!=NULL) && (ptr->count > 0))
    {
        /*if only 1 node available */
        if((ptr->head == ptr->tail)!=0)
        {
            /*free data*/
            free(ptr->head);
            ptr->head  = ptr->tail  = NULL;
            
        }
        /*if not the first node */
        else
        {
            headNext = ptr->head->next;
            free(ptr->head);
            ptr->head  = headNext;
        }
        ptr->count--;
    }
}

/*********************************************************
 * Remove the data from the tail
 ********************************************************/
int queue_del_tail(queue*ptr)
{
    
    node* TailPrev =NULL;
    if((ptr!=NULL) && (ptr->count > 0))
    {
        /*if only 1 node available */
        if(ptr->head == ptr->tail)
        {
            /*free data*/
            free(ptr->head);
            ptr->head  = ptr->tail  = NULL;
            
        }
        /*if not the first node */
        else
        {
            TailPrev = ptr->tail->prev;
            free(ptr->tail);
            ptr->tail  = TailPrev;
            ptr->tail->next = NULL;
            printf("\nprevTail val:%d\n", ((struct data_struct*)TailPrev)->value);
        }
        /*decrement the count */
        ptr->count--;
    }
    return OK;
}
/*********************************************************
 * Create Data to be added to queue
 ********************************************************/
int addData(struct data_struct** d, int val)
{
    struct data_struct* data=NULL;
    /*create memory to store data*/
    data = (struct data_struct*)malloc(sizeof(struct data_struct));
    assert(data!=NULL);
	/*memset structure */
	memset(data, 0, sizeof(struct data_struct));
    /*store value to data */
    data->value = val;
    /*store the allocated memory to be added to queue */
    *d =  data;
    return OK;
}

/*********************************************************
 * Deletes the queue completely and frees the memory for nodes
 ********************************************************/
int queue_delete(queue* ptr)
{
    while(ptr->count)
	{
		queue_del_head(ptr);
	}
}

/*********************************************************
 * Checks if the queue is empty
 ********************************************************/
unsigned int queue_isempty(queue* ptr)
{
    assert(ptr!=NULL);
    if((NULL  == ptr->head) || ( NULL == ptr->tail) || (ptr->count ==0))
    {
        return 1;
    }
}
/*********************************************************
 * Checks if the queue is full
 ********************************************************/
unsigned int queue_isfull(queue*ptr)
{
    assert(ptr!=NULL);
    return ptr->count%QUEUESIZE;
}