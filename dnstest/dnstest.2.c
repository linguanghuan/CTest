#include <resolv.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	MAX_PACKET_SIZE	65536

/* Initialize resp if RES_INIT is not yet set or if res_init in some other
   thread requested re-initializing.  */
int
__res_maybe_init (res_state resp, int preinit);

int
__libc_res_nsearch(res_state statp,
            const char *name,   /* domain name */
            int class, int type,        /* class and type of query */
            u_char *answer,     /* buffer to put answer */
            int anslen,         /* size of answer */
            u_char **answerp);
            
/*
 * 设置IP DNS查询串
 * 将IP地址转置并接上后缀，形成查询串;
 *
 * 参数说明
 * sIpAddress: 查询的IP地址
 * sSuffix：         后缀
 *
 * 返回值
 * DNS查询串
 */
char *GetIPDnsQueryStr(char *psIpAddress,char *psSuffix)
{
#if 0
	转置IP地址sIpAddress存储到字符串sIpAddrTemp;
	将sIpAddrTemp拼接上sSuffix存储到字符串sDnsQuery;
	return sDnsQyery;
#endif
	char sIpTemp[16];
	memset(sIpTemp, 0x0, 16);
	int niIp1,niIp2,niIp3,niIp4;
	niIp1 = niIp2 = niIp3 = niIp4 = 0;
	//按顺序读取出IP段
	if( sscanf(psIpAddress, "%d.%d.%d.%d", &niIp1, &niIp2, &niIp3, &niIp4) != 4 )
	{
		printf("Ip Address:<%s> Format Error!", psIpAddress);
		return NULL;
	}
	//将IP段反过来存放
	snprintf(sIpTemp, 16, "%d.%d.%d.%d", niIp4, niIp3, niIp2, niIp1);
	int niLength;
	if( psSuffix )
	{
		niLength = strlen(sIpTemp) + strlen(psSuffix) + 3;
	}
	else
	{
		niLength = strlen(sIpTemp) + 3;
	}
	char *psDnsQuery = (char *)malloc(niLength * sizeof(char));
	if( psDnsQuery == NULL )
	{
		return NULL;
	}
	memset(psDnsQuery, 0x0, niLength);
	//将转置后的ip接上后缀
	if(psSuffix)
	{
		snprintf(psDnsQuery, niLength-1, "%s.%s", sIpTemp, psSuffix);
	}
	else
	{
		snprintf(psDnsQuery, niLength-1, "%s", sIpTemp);
	}
	return psDnsQuery;

}

int main(int argc, char **argv){
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

        char *psIpAddress = "218.5.81.133";
        char *psDnsQuery = GetIPDnsQueryStr(psIpAddress, "in-addr.arpa");
        printf("psDnsQuery:%s\n", psDnsQuery);
        unsigned char pBuffer[MAX_PACKET_SIZE]={0};
	int nDataLen =__libc_res_nsearch(res, psDnsQuery, C_IN, ns_t_ptr, pBuffer, MAX_PACKET_SIZE - 1, NULL);
	printf("pBuffer:%s\n",pBuffer);
        printf("ok----------\n");
        return 0;
}

