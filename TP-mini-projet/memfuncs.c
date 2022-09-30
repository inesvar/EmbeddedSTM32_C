#include <stddef.h>
#include <stdio.h>
#include <string.h>
//#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t count)
{
    char *dest2 = (char *)dest;
    char *src2 = (char *)src;
    for (int i = 0; i < count; i++)
    {
        *dest2++ = *src2++;
    }
    return dest;
}

void *memmove(void *dest, const void *src, size_t count)
{
    char *temp_dest;
    char *dest2 = (char *)dest;
    char *src2 = (char *)src;
    for (int i = 0; i < count; i++)
    {
        *temp_dest++ = *src2++;
    }
    for (int i = 0; i < count; i++)
    {
        *dest2++ = *temp_dest++;
    }
    return dest;
}

void *memset(void *dest, int ch, size_t count)
{
    char ch2 = (char)ch;
    char *dest2 = (char *)dest;
    for (int i = 0; i < count; i++)
    {
        *dest2++ = ch2;
    }
    return dest;
}

int memcmp(const void *lhs, const void *rhs, size_t count)
{
    char *lhs2 = (char *)lhs;
    char *rhs2 = (char *)rhs;
    for (int i = 0; i < count; i++)
    {
        if (*lhs2 > *rhs2)
        {
            return 1;
        }
        else if (*rhs2 > *lhs2)
        {
            return -1;
        }
        else
        {
            lhs2++;
            rhs2++;
        }
    }
    return 0;
}
