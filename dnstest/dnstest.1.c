#include <resolv.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Initialize resp if RES_INIT is not yet set or if res_init in some other
   thread requested re-initializing.  */
int
__res_maybe_init (res_state resp, int preinit);

int
__libc_res_nsearch(res_state statp,
	    const char *name,	/* domain name */
	    int class, int type,	/* class and type of query */
	    u_char *answer,	/* buffer to put answer */
	    int anslen,		/* size of answer */
	    u_char **answerp);
	    
/*
 * ip ptr 格式查询字符串
 */
static void DnsMakePtrString(char *psIp, char *psPtrString, int nPtrStrLen)
{
	if(NULL == psIp || NULL == psPtrString)
		return;

	if(NULL == strstr(psIp, ".in-addr.arpa"))
	{
		int nIp1 = 0, nIp2 = 0, nIp3 = 0, nIp4 = 0;
		sscanf(psIp, "%d.%d.%d.%d", &nIp1, &nIp2, &nIp3, &nIp4 );
		snprintf(psPtrString, nPtrStrLen, "%d.%d.%d.%d.in-addr.arpa", nIp4, nIp3, nIp2, nIp1);
	}
	else
	{
		snprintf(psPtrString, nPtrStrLen, "%s", psIp);
	}
}


int main(){
	struct __res_state *res;
	res=(struct __res_state *)malloc(sizeof(struct __res_state ));
	memset(res, 0x0, sizeof(struct __res_state));
	res->retrans = 2;
	res->retry = 1;

	if( -1 == __res_maybe_init(res,1))
	{
		free(res);
		return 1;
	}
	char sPtrString[256] = { 0 };
	DnsMakePtrString(pQueryStr, sPtrString, 256);
	print("sPtrString:%s\n", sPtrString);
//	int nDataLen =__libc_res_nsearch(resdup, querystr, C_IN, type, qb->ptDnsData->pBuffer, MAX_PACKET_SIZE - 1, NULL);
	printf("ok----------\n");
	return 0;
}

