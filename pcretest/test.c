#include <stdio.h>
#include <string.h>
#include <pcre.h>

#define OK 0
#define ERR 1
#define OVECCOUNT 512

typedef struct _REGEX_MATCH_RESULT
{
	int nMatchPos;
	int nMatchLen;
}RegexMatchResult;

RegexMatchResult* StrRegexMatch(const char *psString, const char *psPattern, int *nMatches)
{
	RegexMatchResult *ptRegexMatchResult = NULL;
	int niErrOffset;
	const char *sError;
	pcre *ptRe = pcre_compile(psPattern, PCRE_CASELESS, &sError, &niErrOffset, NULL);

	*nMatches = 0;
	if(NULL == ptRe)
	{
		return NULL;
	}

	size_t nStrLen = strlen(psString);

	int niOvector[OVECCOUNT] = {0};
	int niRc = pcre_exec(ptRe, NULL, psString, nStrLen, 0, 0, niOvector, OVECCOUNT);
	if(niRc > 0)
	{
		ptRegexMatchResult = (RegexMatchResult *)calloc(niRc, sizeof(RegexMatchResult));
		int i = 0;
		for(i = 0; i < niRc && i < OVECCOUNT; i++)
		{
			ptRegexMatchResult[i].nMatchPos = niOvector[2 * i];
			ptRegexMatchResult[i].nMatchLen = niOvector[2 * i + 1] - niOvector[2 * i];
		}
		*nMatches = niRc;
	}

	free(ptRe);
	return ptRegexMatchResult;
}

int main(int argc, char *argv[])
{
	//char *psPattern = "(.+\\..+)";
	//char *psPattern = "(.+)''(.+)";
	//char *psPattern = "=\\?(.+)\\?([BbQq])\\?(.+)\\?=";
	char *psPatterns[3] = {     \
			"(.+\\..+)",    \
			"(.+)''(.+)",    \
			"=\\?(.+)\\?([BbQq])\\?(.+)\\?="   \
		};
	char *names[10]={ \
		"domain_302_1436499636_out.txt", \
		"gb18030''%D6%D0%CE%C4%B8%BD%BC%FE%B2%E2%CA%D4%2E%74%78%74",	\
		"=?gbk?Q?=D6=D0=CE=C4=C2=D2=C2=EB=C1=CB=C2=F0=2Etxt?=",	\
		"=?gb2312?B?1tDOxLi9vP4udHh0?=",   \
	};
	int i = 0;
	for(i=0; i< 10; i++)
	{
		printf("-----------------------------------\n");
		if (NULL == names[i])
		{
			break;
		}
		printf("%d:%s\n", i, names[i]);
		RegexMatchResult* ptResult = NULL;
		int nMatches = 0;
		char *psTemp = names[i];
		int j = 0;
		for (j=0; j<3; j++)
		{
			char *psPattern = psPatterns[j];
			ptResult = StrRegexMatch(psTemp, psPattern, &nMatches);
			if (ptResult)
			{
				printf("%d:%s\n", j, psPattern);
				printf("pos:%d, len:%d, matches:%d\n", ptResult->nMatchPos, ptResult->nMatchLen, nMatches);
			}
		}
	}
	return OK;
}
