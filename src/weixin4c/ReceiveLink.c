#include "weixin4c_public.h"
#include "weixin4c_private.h"

int ReceiveLink( struct Weixin4cEnv *penv , char *post_data , int post_data_len , xml *p_req )
{
	xml	rsp ;
	char	output_buffer[ 4096 * 100 ] ;
	int	output_buflen ;
	int	output_bufsize ;
	char	rsp_buffer[ 4096 * 110 ] ;
	int	rsp_buflen ;
	
	int	nret = 0 ;
	
	TakeoffCDATA( p_req->ToUserName );
	TakeoffCDATA( p_req->FromUserName );
	TakeoffCDATA( p_req->Title );
	TakeoffCDATA( p_req->Description );
	TakeoffCDATA( p_req->Url );
	
	memset( output_buffer , 0x00 , sizeof(output_buffer) );
	output_buflen = 0 ;
	output_bufsize = sizeof(output_buffer) ;
	if( penv->pconf->funcs.pfuncReceiveLinkProc )
	{
		SetLogFile( "%s/log/%s_ReceiveLinkProc.log" , penv->pconf->home , penv->pconf->project_name );
		nret = penv->pconf->funcs.pfuncReceiveLinkProc( penv->pconf->user_data , p_req , output_buffer , & output_buflen , & output_bufsize ) ;
		SetLogFile( "%s/log/%s_weixin4c.log" , penv->pconf->home , penv->pconf->project_name );
		if( nret )
		{
			ErrorLog( __FILE__ , __LINE__ , "pfuncReceiveLinkProc failed[%d]" , nret );
		}
		else
		{
			InfoLog( __FILE__ , __LINE__ , "pfuncReceiveLinkProc ok" );
		}
	}
	
	memset( & rsp , 0x00 , sizeof(xml) );
	snprintf( rsp.ToUserName , sizeof(rsp.ToUserName)-1 , "<![CDATA[%s]]>" , p_req->FromUserName );
	snprintf( rsp.FromUserName , sizeof(rsp.FromUserName)-1 , "<![CDATA[%s]]>" , p_req->ToUserName );
	rsp.CreateTime = (int)time(NULL) ;
	strcpy( rsp.MsgType , p_req->MsgType );
	
	memset( rsp_buffer , 0x00 , sizeof(rsp_buffer) );
	rsp_buflen = sizeof(rsp_buffer) - 1 ;
	nret = DSCSERIALIZE_XML_xml( & rsp , "GB18030" , rsp_buffer , & rsp_buflen ) ;
	if( nret )
	{
		ErrorLog( __FILE__ , __LINE__ , "DSCSERIALIZE_XML_xml failed[%d]" , nret );
	}
	else
	{
		InfoLog( __FILE__ , __LINE__ , "DSCSERIALIZE_XML_xml ok" );
		InfoLog( __FILE__ , __LINE__ , "rsp xml[%.*s]" , rsp_buflen-41 , rsp_buffer+41 );
		printf( "%.*s" , rsp_buflen-41 , rsp_buffer+41 );
	}
	
	return 0;
}

