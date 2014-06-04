#include <stdlib.h>

#define malloc dont user malloc directly, use MALLOC instead
#define MALLOC(num,type) (type *)alloc((num) * sizeof(type))
extern void *alloc(size_t size);
