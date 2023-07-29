# Password Generator by Thilia
[English](./README.md) | 简体中文

<br>这是一个基于除法的密码生成器。<br/>

# 原理
<br>总所周知, 任何非0自然数除以一个`分解素因数, 其中包括除了2或5以外的素数的数`, 都无法除尽。<br/>
<br>而仔细观察, 2 * 5 = 10, 10正是十进制数字的基数。<br/>
<br>而在程序中, 除法的求小数部分大概可以用这样一个函数概括:<br/>
```c
int main(void)
{
	unsigned int a = 3141; //被除数
	unsigned int b = 5926; //除数
	unsigned int digits = 16; //小数点后多少位
	unsigned int base = 10; //基数
	char str[17]; //储存字符串
	a %= b; //让a小于b, 从而保证求出的是小数
	for (unsigned int i = 0; i < digits; i++)
	{
		a = (a % b) * base; //被除数除以除数的余数乘上基数, 作为新的被除数去除
		str[i] = (a / b) + '0';
	}
	str[16] = '\0';
	printf("3141 / 5926 = 0.%s", str);
}
```
<br>从结果中不难发现, 小数部分各数位上的数都小于10, 即小于`base`。若把`base`换成16再运行, 那么结果各数都小于16。<br/>
<br>由此不难看出, 只要将`base`换成其他的数, 所得结果必定小于其本身。<br/>
<br>那么可以将其设置为(26+26+10+?), 即26个大写字母、26个小写字母与、10个数字还有?个的特殊字符, 并设置字符对应关系, 那么就可以将各个数位上的数字转换成可打印字符, 然后就能得出一串字符串了, 可以直接拿去当密码用。<br/>
<br>当被除数、除数、基数、对应字符的函数都一样时, 所计算出的值也都相同。<br/>
<br>即, 你只需要记住主密码(一般作被除数), 除数填服务名称就行。<br/>
<br>将他们通过Hash函数转换成整型, 并拿去相除, 就可以得到最终的结果了。<br/>
<br>不过以这种方式来的话, 与其说是生成, 不如说是计算, 但都无所谓啦, 能用就行。<br/>

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
<br>作为库使用只需要`GpAPI.c`和`GpAP.h`两个文件。<br/>
<br>引用:<br/>
```c
#include "GpAPI.h"
```
<br>`GpAPI.h`提供了两个方法:<br/>
```c
void GenPasswd(FILE *outstream, uint64_t a, uint64_t b, unsigned int maxsize, volatile unsigned int *sizedst, char *pwd_chars, unsigned int pwd_chars_count);
void GenPasswdByString(FILE *outstream, char *a, char *b, unsigned int maxsize, volatile unsigned int *sizedst, char *pwd_chars, unsigned int pwd_chars_count);
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
