/*
 *  Password Generator in C.
 *  This is an API of Password Generator.
 *  Copyright (C) 2023  Thilia
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *  Email: tpr4int@skiff.com
 */

#include "ThGpAPI.h"

unsigned int find_up_prime(unsigned int number);
_Bool isprime(unsigned int number);
char get_pwd_char(unsigned int serial, char *pwd_chars, unsigned int pwd_chars_count);
unsigned int BKDRHash(char *str);

void ThGenPasswdByString(FILE *outstream, char *a, char *b, unsigned int maxsize, volatile unsigned int *sizedst, char *pwd_chars, unsigned int pwd_chars_count)
{
	GenPasswd(outstream, BKDRHash(a), BKDRHash(b), maxsize, sizedst, pwd_chars, pwd_chars_count);
}

void ThGenPasswd(FILE *outstream, uint64_t a, uint64_t b, unsigned int maxsize, volatile unsigned int *sizedst, char *pwd_chars, unsigned int pwd_chars_count)
{
	//Setting env
	unsigned int size = 0;
	sizedst = (sizedst == NULL) ? &size : sizedst;
	pwd_chars_count = (pwd_chars == NULL) ? strlen(DEFAULT_PWD_CHARS) : pwd_chars_count;
	pwd_chars = (pwd_chars == NULL) ? DEFAULT_PWD_CHARS : pwd_chars;
	//Define variables
	unsigned int truebase = 62 + pwd_chars_count;
	unsigned int base = find_up_prime(126);
	long unsigned int tempv = 0;
	//Generate
	for (*sizedst = 0; *sizedst < maxsize; (*sizedst)++)
	{
		tempv = (a / b) % truebase;
		tempv = get_pwd_char(tempv, pwd_chars, pwd_chars_count);
		fwrite(&tempv, sizeof(char), 1, outstream);
		a = (a % b) * base;
	}
	fflush(outstream);
}

char get_pwd_char(unsigned int serial, char *pwd_chars, unsigned int pwd_chars_count)
{
	if (serial < 10)
	{
		return serial + '0';
	}
	else if (serial < 36)
	{
		return serial + 'a' - 10;
	}
	else if (serial < 62)
	{
		return serial + 'A' - 36;
	}
	else if (serial < (62 + pwd_chars_count))
	{
		return pwd_chars[serial - 62];
	}
	return '_';
}

unsigned int find_up_prime(unsigned int number)
{
	unsigned int max = number;
	while (!isprime(max))
	{
		max++;
	}
	return max;
}

_Bool isprime(unsigned int number)
{
	if (number < 2)
	{
		return 0;
	}
	for (unsigned int i = 3; i < number; i += 2)
	{
		if (number % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

/*
 * BKDR Hash Function
 * From https://byvoid.com/zhs/blog/string-hash-compare/
 */
uint32_t BKDRHash(char *str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;

	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}
