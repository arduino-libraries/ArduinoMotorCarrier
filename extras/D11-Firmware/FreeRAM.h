extern "C" char *sbrk(int i);
int FreeRam (void)
{
    char stack_dummy = 0;
    return &stack_dummy - sbrk(0);
}
