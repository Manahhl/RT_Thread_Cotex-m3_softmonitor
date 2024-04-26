/**
 * @Author: jiagebu jack shiyanerzhong@outlook.com
 * @Date: 2024-04-25 14:42:25
 * @LastEditors: jiagebu jack shiyanerzhong@outlook.com
 * @LastEditTime: 2024-04-25 15:07:54
 * @FilePath: \Projectd:\Git_projects\RT_Thread_From0to1_softmonitor\rtthread3.0.3\src\kservice.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include "main.h"

/// @brief 将函数指定个数的字符串从一个地方拷贝到另一个地方
/// @param destination 
/// @param source 
/// @param n 
/// @return 结果
char *rt_strncpy(char *destination, const char *source, rt_ubase_t n)
{
    if (n!=0)
    {
        char *d = destination;
        const char *s = source;
        do{
            if ((*d++ = *s++) == 0)
            {
                //null pad the remanning n-1 bytes
                while (--n != 0)
                {
                    *d++ = 0;
                }
                break;
            }
        } while (--n != 0);
    }
    return (destination);
}
