# Password Generator by Thilia
[English](./README.md) | 简体中文

<br>这是一个基于除法的密码生成器。<br/>

# 原理
<br>总所周知, 任何非0自然数除以一个`分解素因数后其中包括除了2或5以外的素数的数`, 都无法除尽。<br/>
<br>2 * 5 = 10, 正是十进制数字的基数。<br/>
<br>而在程序中, 除法的求小数部分(以十进制除法为例)大概可以用这样一个函数概括(模拟笔算):<br/>
```c
int main(void)
{
	unsigned int a = 3141; //被除数
	unsigned int b = 5926; //除数
	unsigned int digits = 16; //小数点后多少位
	unsigned int base = 10; //基数
	char str[digits + 1]; //储存字符串
	a %= b; //a此时必定小于b, 保证求出的是小数
	for (unsigned int i = 0; i < digits; i++)
	{
		a = (a % b) * base; //被除数除以除数的余数乘上基数, 作为新的被除数去除
		str[i] = (a / b) + '0';
	}
	str[16] = '\0'; //给字符增添结束符('\0')
	printf("3141 / 5926 = 0.%s", str);
}
```
<br>若将基数改为`x`, 那么各位小数的值均不会超过`x`。由此可以写一个函数, 将值与密码字符对应, 函数不变, 值对应的字符也不会改变。<br/>
<br>且由于无论处于什么环境, 相同数据的Hash值一定相同, 故可确保生成的密码始终相同。<br/>
<br>即，你只需要用的同一个Hash函数, 同一个密码对应字符的函数, 同一个基数, 同一个输入, 那么输出的密码一定不变。（事实上这程序没啥太大改变，你只需要记住项目网址以及生成时用的版本即可）

# 编译
## Windows
```shell
gcc *.c *.h -o thgenpwd.exe
```
## Linux
```shell
gcc *.c *.h -o thgenpwd
```

# 用法
## 直接作为控制台程序来用
```shell
thgenpwd [mainpwd] [name] [size]
```
<br>如果参数只有`mainpwd`, 那么接下来你就得输入`name`和`size`。<br/>
<br>如果参数有`mainpwd`和`name`, 那么接下来你只需输入`size`。<br/>
<br>如果参数全部写了, 那接下来你就什么也不用写。<br/>
<br>E.g:<br>
```shell
thgenpwd mypwd Google 16
```
## 作为库使用
<br>作为库使用只需要`ThGpAPI.c`和`ThGpAPI.h`两个文件。<br/>
<br>引用:<br/>
```c
#include "ThGpAPI.h"
```
<br>`ThGpAPI.h`提供了两个方法:<br/>
```c
void ThGenPasswd(FILE *outstream, uint64_t a, uint64_t b, unsigned int maxsize, volatile unsigned int *sizedst, char *pwd_chars, unsigned int pwd_chars_count);
void ThGenPasswdByString(FILE *outstream, char *a, char *b, unsigned int maxsize, volatile unsigned int *sizedst, char *pwd_chars, unsigned int pwd_chars_count);
```
### 其中名称的解释
<br>`outstream`: 输出的文件流<br/>
<br>`GenPasswd`的`a`: 被除数<br/>
<br>`GenPasswd`的`b`: 除数<br/>
<br>`GenPasswdByString`的`a`: 主密码<br/>
<br>`GenPasswdByString`的`a`: 服务名称<br/>
<br>`maxsize`: 文件大小(由于字符占一个字节, 所以也算密码的长短)<br/>
<br>`sizedst`: 目前文件大小的指针, 可以在外部显示进度。(如果为NULL, 将会使用函数内的变量)<br/>
<br>`pwd_chars`: 特殊字符的数组。(如果为NULL, 将使用默认值, 即`DEFAULT_PWD_CHARS`)<br/>
<br>`pwd_chars_count`: 特殊字符数组的长度。(如果`pwd_chars`为NULL, 将会使用`DEFAULT_PWD_CHARS`的长度)<br/>
### 例子:
```c
#include <stdio.h>
#include "GpAPI.h"

int main(void)
{
	FILE *fp = fopen("test.txt", "w");
	GenPasswd(fp, 314159, 265358, 1024, NULL, NULL, 0);
	fclose(fp);
}
```
