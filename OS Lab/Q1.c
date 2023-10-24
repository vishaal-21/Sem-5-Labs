#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct mab
{
    int offset;
    int size;
    int allocated;
    struct mab *next;
    struct mab *prev;
} Mab;

typedef Mab *MabPtr;

MabPtr memChk(MabPtr m, int size)
{
    if (!m->allocated && m->size >= size)
        return m;
    return NULL;
}

MabPtr memAllocBestFit(MabPtr m, int size)
{
    MabPtr allocatedBlock;
    while(m!=NULL)
    {

    }
}

MabPtr memAllocWorstFit(MabPtr m, int size)
{
}

MabPtr memFree(MabPtr m)
{
}

MabPtr memMerge(MabPtr m)
{
}

MabPtr memSplit(MabPtr m, int size)
{
}

void displayMemory(MabPtr m)
{
    printf("MEMORY\n");
    printf("Size\n-----\n");
    while (m != NULL)
    {
        printf("%d\n", m->size);
        m = m->next;
    }
}

void displayProcess(int size[], int n)
{
    printf("\nPROCESSES\n");
    printf("No.\tSize\n-------------\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", i + 1, size[i]);
}

void main()
{
    MabPtr head, block1, block2, block3, block4, block5;

    block1 = (MabPtr)malloc(sizeof(Mab));
    block2 = (MabPtr)malloc(sizeof(Mab));
    block3 = (MabPtr)malloc(sizeof(Mab));
    block4 = (MabPtr)malloc(sizeof(Mab));
    block5 = (MabPtr)malloc(sizeof(Mab));

    block1->offset = 0;
    block1->size = 100;
    block1->allocated = 0;
    block1->prev = NULL;
    block1->next = block2;

    block2->offset = 100;
    block2->size = 500;
    block2->allocated = 0;
    block2->prev = block1;
    block2->next = block3;

    block3->offset = 600;
    block3->size = 200;
    block3->allocated = 0;
    block3->prev = block2;
    block3->next = block4;

    block4->offset = 800;
    block4->size = 450;
    block4->allocated = 0;
    block4->prev = block3;
    block4->next = block5;

    block5->offset = 1250;
    block5->size = 600;
    block5->allocated = 0;
    block5->prev = block4;
    block5->next = NULL;

    int process_size[] = {212, 417, 112, 426};
    int proc_alloc[] = {0, 0, 0, 0};
    int numProccess = sizeof(process_size) / sizeof(process_size[0]);

    head = block1;
    MabPtr temp = head;

    displayMemory(head);
    displayProcess(process_size, numProccess);

    printf("\nFIRST FIT\n----------------------------------------------------\n");
    for (int i = 0; i < numProccess; i++)
    {
        while (temp != NULL)
        {
            MabPtr freeMem = memChk(temp, process_size[i]);
            if (freeMem != NULL)
            {
                printf("Process of size %d allocated to memory of size %d\n", process_size[i], freeMem->size);
                proc_alloc[i] = 1;
                freeMem->allocated = 1;
                temp = temp->next;
                break;
            }

            temp = temp->next;
        }
    }

    for (int i = 0; i < numProccess; i++)
        if (proc_alloc[i] == 0)
            printf("Process of size %d remains unallocated to any block\n", process_size[i]);

    printf("Best Fit\n----------------------------------------------------\n");

    // printf("Worst Fit\n");
}
