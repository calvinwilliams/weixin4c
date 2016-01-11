#include "weixin4c_public.h"

char *PUBStringNoEnter( char *str )
{
	char	*ptr = NULL ;
	
	if( str == NULL )
		return NULL;
	
	for( ptr = str + strlen(str) - 1 ; ptr >= str ; ptr-- )
	{
		if( (*ptr) == '\r' || (*ptr) == '\n' )
			(*ptr) = '\0' ;
		else
			break;
	}
	
	return str;
}

int PUBHexExpand( char *HexBuf , int HexBufLen , char *AscBuf )
{
	int	i,j=0;
	char	c;
	
	for(i=0;i<HexBufLen;i++){
		c=(HexBuf[i]>>4)&0x0f;
		if(c<=9) AscBuf[j++]=c+'0';
		else AscBuf[j++]=c+'a'-10;

		c=HexBuf[i]&0x0f;
		if(c<=9) AscBuf[j++]=c+'0';
		else AscBuf[j++]=c+'a'-10;
		}
	AscBuf[j]=0;
	return(0);
}

void TakeoffCDATA( char *str_with_cdata )
{
	if( memcmp( str_with_cdata , "<![CDATA[" , 9 ) == 0 )
	{
		int	len ;
		len = strlen(str_with_cdata) ;
		str_with_cdata[len-3] = '\0' ;
		memmove( str_with_cdata , str_with_cdata+9 , len-3-9+1 );
	}
	
	return;
}

