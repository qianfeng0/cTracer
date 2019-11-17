#include <stdio.h>
#include <malloc.h>
// #include <xhook.h>
#include <ctracer.h>

void *my_malloc(size_t size)
{
    printf("%zu bytes memory are allocated by libtest.so\n", size);
    // return malloc(size);
}

int main(){
    ctracer_init();
    // xhook_enable_debug(1);
    // xhook_register("tracerTest", "malloc", (void*)my_malloc, NULL);
    // printf("start xhook_refresh\n");
    // xhook_refresh(0);

    void* p1 = malloc(10);
    void* p2 = malloc(10);
    free(p1);
    void* p3 = malloc(10);
    free(p2);
    free(p3);

    p1 = malloc(20);
    p1 = realloc(p1, 20);
    p2 = calloc(10, 20);
    printf("hello\n");
    ctracer_scan_mem();
    return 0;
}