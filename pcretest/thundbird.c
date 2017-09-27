// gb18030''%D6%D0%CE%C4%B8%BD%BC%FE%B2%E2%CA%D4%2E%74%78%74

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define OK 0
#define ERR 1

int main()
{
	char *psSourceMime = "gb18030''%D6%D0%CE%C4%B8%BD%BC%FE%B2%E2%CA%D4%2E%74%78%74";
	printf("source:%s\n", psSourceMime);
	char *psTemp = psSourceMime;

	char sCharset[65] = { 0 };
	char *psCharsetEnd = strchr(psTemp, '\'');
	if(NULL == psCharsetEnd)
	{
		return ERR;
	}
	int charsetLen = psCharsetEnd - psTemp;
	strncpy(sCharset, psTemp,  charsetLen>64 ? 64 : charsetLen);
	printf("charset:%s\n", sCharset);
	if (*(psCharsetEnd +1) != '\'')
	{
		return ERR;
	}
	psTemp = psCharsetEnd + 2;
	int sourceLen = strlen(psSourceMime);
	
	int nContentLen = 2 * (sourceLen - charsetLen -2);
	char *psContent = NULL;
	if(nContentLen <= 0)
		return ERR;
	psContent = (char *)malloc(nContentLen);
	memset(psContent, 0, nContentLen);
	strncpy(psContent, psTemp, sourceLen - charsetLen -2);
	printf("content:%s\n", psContent);

	return OK;
}
