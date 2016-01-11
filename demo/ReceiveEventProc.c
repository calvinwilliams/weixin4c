#include "weixin4c.h"

funcReceiveEventProc ReceiveEventProc ;
int ReceiveEventProc( void *user_data , xml *p_req , char *output_buffer , int *p_output_buflen , int *p_output_bufsize )
{
	int		n ;
	
	if( strcmp( p_req->Event , "<![CDATA[subscribe]]>" ) == 0 )
	{
		(*p_output_buflen) += snprintf( output_buffer+(*p_output_buflen) , (*p_output_bufsize)-1 - (*p_output_buflen) ,
			"��ӭ����"
			);
	}
	else if( strcmp( p_req->Event , "<![CDATA[unsubscribe]]>" ) == 0 )
	{
		(*p_output_buflen) += snprintf( output_buffer+(*p_output_buflen) , (*p_output_bufsize)-1 - (*p_output_buflen) ,
			"�ټ�"
			);
	}
	
	InfoLog( __FILE__ , __LINE__ , "�ı�����ǰ[%s]" , output_buffer );
	n = PUBConvCharacterCode( "GB18030" , "UTF-8" , output_buffer , (*p_output_buflen) , (*p_output_bufsize) );
	if( n < 0 )
	{
		ErrorLog( __FILE__ , __LINE__ , "PUBConvCharacterCode failed[%d]" , n );
		return -1;
	}
	InfoLog( __FILE__ , __LINE__ , "�ı������[%s]" , output_buffer );
	(*p_output_buflen) = n ;
	
	return 0;
}

