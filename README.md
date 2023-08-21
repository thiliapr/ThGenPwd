# Password Generator by Thilia
English | [简体中文](./README.zh-cn.md)

<br>A password generator based on division.<br/>

# Principle
<br>There is too much complex content here, and I cannot write it fluently in English, so please refer to the Chinese introduction [here](.//README.zh-cn.md#%E5%8E%9F%E7%90%86).<br/>
<br>If you could complete this part, I would greatly appreciate it!<br/>

# Build
## Windows
```shell
gcc *.c *.h -o thgenpwd.exe
```
## Linux
```shell
gcc *.c *.h -o thgenpwd
```

# Usage
## As a console program
```shell
thgenpwd [mainpwd] [name] [size]
```
<br>You can only write a few parameters, and the remaining program will require you to input them to complete.<br/>
<br>E.g:<br>
```shell
thgenpwd mypwd Google 16
```
## As a library
<br>As a library, only two files are required: `ThGpAPI.c` and `ThGpAPI.h`.<br/>
<br>Include:<br/>
```c
#include "ThGpAPI.h"
```
<br>`ThGpAPI.h` provides two methods:<br/>
```c
void GenPasswd(FILE *outstream, uint64_t a, uint64_t b, unsigned int maxsize, volatile unsigned int *sizedst, char *pwd_chars, unsigned int pwd_chars_count);
void GenPasswdByString(FILE *outstream, char *a, char *b, unsigned int maxsize, volatile unsigned int *sizedst, char *pwd_chars, unsigned int pwd_chars_count);
```
### Explanation of names
<br>There is too much complex content here, and I cannot write it fluently in English, so please refer to the Chinese introduction [here](./README.zh-cn.md#%E5%85%B6%E4%B8%AD%E5%90%8D%E7%A7%B0%E7%9A%84%E8%A7%A3%E9%87%8A).<br/>
<br>If you could complete this part, I would greatly appreciate it!<br/>
### E.g
```c
#include <stdio.h>
#include "ThGpAPI.h"

int main(void)
{
	FILE *fp = fopen("test.txt", "w");
	GenPasswd(fp, 314159, 265358, 1024, NULL, NULL, 0);
	fclose(fp);
}
```
