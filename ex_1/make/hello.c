#include <stdio.h>
#include "min.h"
#include "max.h"

int main()
{
    int a1 = 33;
    int a2 = 21;
    int maxNum = max(a1, a2);
    int minNum = min(a1, a2);
    printf("the max value is %d\nthe min value is %d\n", maxNum, minNum);
    return 0;    
}
