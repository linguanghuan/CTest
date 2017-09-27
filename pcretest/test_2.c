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
	char *psTmp = "小";

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
	int nMatches = 0;
	RegexMatchResult* ptResult = NULL;
	////ptResult = StrRegexMatch("xx反馈xxx", "[小].{0,3}", &nMatches);
	////ptResult = StrRegexMatch("反馈", "[小].{0,3}", &nMatches);
	////ptResult = StrRegexMatch("反", "[(小)].{0,3}", &nMatches);
	//ptResult = StrRegexMatch("反", "[小].{0,3}", &nMatches);
	ptResult = StrRegexMatch("反", "(小).{2}", &nMatches);
	//ptResult = StrRegexMatch("xx反馈xxx", "小].{0,3}", &nMatches);
	//ptResult = StrRegexMatch("xx反馈xxx", "小.{0,3}", &nMatches);
	//ptResult = StrRegexMatch("xx反馈xxx", "小", &nMatches);
	//ptResult = StrRegexMatch("xx反馈xxx", "小.", &nMatches);
	//ptResult = StrRegexMatch("xx反馈xxx", "小..", &nMatches);
	//ptResult = StrRegexMatch("xx反馈xxx", "小...", &nMatches);
	
	if (ptResult)
	{
		printf("pos:%d, len:%d, matches:%d\n", ptResult->nMatchPos, ptResult->nMatchLen, nMatches);
	}

	return OK;
}
