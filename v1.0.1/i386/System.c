/*****************************************************************************
 *                                                                           *
 *  uCUnit - A unit testing framework for microcontrollers                   *
 *                                                                           *
 *  (C) 2007 - 2008 Sven Stefan Krauss                                       *
 *                  https://www.ucunit.org                                   *
 *                                                                           *
 *  File        : System.c                                                   *
 *  Description : System dependent functions used by uCUnit.                 *
 *  Author      : Sven Stefan Krauss                                         *
 *  Contact     : www.ucunit.org                                             *
 *                                                                           *
 *****************************************************************************/

/*
 * This file is part of ucUnit.
 *
 * You can redistribute and/or modify it under the terms of the
 * Common Public License as published by IBM Corporation; either
 * version 1.0 of the License, or (at your option) any later version.
 *
 * uCUnit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Common Public License for more details.
 *
 * You should have received a copy of the Common Public License
 * along with uCUnit.
 *
 * It may also be available at the following URL:
 *       http://www.opensource.org/licenses/cpl1.0.txt
 *
 * If you cannot obtain a copy of the License, please contact the
 * author.
 */
#include "../System.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void System_Init(void)
{
}

void System_Shutdown(void)
{
  fflush(stdout);
}

void System_Recover(void)
{
}

void System_Safestate(void)
{
}

void System_WriteString(char const* msg)
{
  printf("%s", msg);
  fflush(stdout);
}

void System_WriteStringQuoted(char const* msg)
{
  while (*msg != '\0')
  {
    if (*msg != '\"')
    {
      putchar(*msg);
    }
    else
    {
      putchar('\\');
      putchar('\"');
    }

    msg++;
  }
}

void System_WriteInt(int n)
{
  printf("%i", n);
  fflush(stdout);
}
