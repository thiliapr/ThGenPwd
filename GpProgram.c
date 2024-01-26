/*
 *  Password Generator in C.
 *  This is a program for users to call GpAPI to generate password. 
 *  Copyright (C) 2023-2024  Thilia
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

#include "GpProgram.h"

int main(int argc, char const *argv[])
{
	char args[2][16] = {0};
	unsigned int maxsize = 0;
	for (int i = 1; i < ((argc > 3) ? 3 : argc); i++)
	{
		unsigned char d = 2;
		strcpy(args[i - 1], argv[i]);
	}
	if (argc < 2)
	{
		printf("Main Password (E.g: mypwd_someone) (No Space) = ");
		fgets(args[0], 16, stdin);
		args[0][strlen(args[0]) - 1] = 0;
	}
	if (argc < 3)
	{
		printf("Name of Sevice (E.g: Google) = ");
		fgets(args[1], 16, stdin);
		args[1][strlen(args[1]) - 1] = 0;
	}
	if (argc > 3)
	{
		sscanf(argv[3], "%u", &maxsize);
	}
	else
	{
		printf("Size = ");
		scanf("%u", &maxsize);
	}
	ThGenPasswdByString(stdout, args[0], args[1], maxsize, NULL, NULL, 0);
	return 0;
}
