#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
        if (q == NULL)
                return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: put a new process to queue [q] */
        if (q == NULL || proc == NULL) return;

        if (q->size == MAX_QUEUE_SIZE) return;

        int i = q->size - 1;

        while (i >= 0 && (q->proc[i]->prio > proc->prio))
        {
                q->proc [i + 1] = q->proc[i];
                i--;
        }

        q->proc [i + 1] = proc;
        q->size++;
}

struct pcb_t *dequeue(struct queue_t *q)
{
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */

        if (q == NULL || q->size == 0) return NULL;

        struct pcb_t* maxPrior = q->proc[0];

        for (int i=0; i < q->size - 1; i++) q->proc [i] = q->proc [i + 1];

        q->proc [q->size - 1] = NULL;
        q->size--;
        return maxPrior;
}

struct pcb_t *purgequeue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: remove a specific item from queue
         * */
        if (q == NULL || proc == NULL || q->size == 0)
                return NULL;

        int idx = -1;
        for (int i = 0; i < q->size; i++) {
                if (q->proc[i] == proc) {
                        idx = i;
                        break;
                }
        }

        if (idx == -1)
                return NULL;

        /* remove element at idx and shift left */
        for (int i = idx + 1; i < q->size; i++)
                q->proc[i - 1] = q->proc[i];

        q->size--;
        return proc;
}