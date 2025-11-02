#include"1_seqstack.h"
void initstack(seqstack *s)
{
    s->base=(elemtype*)malloc(sizeof(elemtype)*STACK_INIT_SIZE);
    assert(s!=NULL);
    s->capacity=STACK_INIT_SIZE;
    s->top=0;
}
int main()
{
    seqstack st;
    initstack(&st)
}