#include "weixin4c_public.h"

int PUBGetUrlParamPtr( char *key , char **pp_value , int *p_value_len )
{
	char	*QUERY_STRING = NULL ;
	char	*value = NULL ;
	char	*p = NULL ;
	
	QUERY_STRING = getenv("QUERY_STRING") ;
	if( QUERY_STRING == NULL )
		return -1;
	
	value = strstr( QUERY_STRING , key ) ;
	if( value == NULL )
		return -2;
	
	if( value != QUERY_STRING && (*(value-1)) != '&' )
		return -3;
	
	value += strlen(key) ;
	
	if( (*value) != '=' )
		return -4;
	
	value++;
	
	for( p = value ; (*p) && (*p) != '&' ; p++ )
		;
	if( pp_value )
		(*pp_value) = value ;
	if( p_value_len )
		(*p_value_len) = p - (*pp_value) ;
	
	return 0;
}

int PUBGetUrlParam( char *key , char *value , int value_size )
{
	char	*p_value = NULL ;
	int	value_len ;
	
	int	nret = 0 ;
	
	nret = PUBGetUrlParamPtr( key , & p_value , & value_len ) ;
	if( nret )
		return nret;
	
	if( value_len > value_size-1 )
		return -5;
	
	memset( value , 0x00 , value_size );
	memcpy( value , p_value , value_len );
	
	return 0;
}

int PUBDupUrlParam( char *key , char **pp_value )
{
	char	*p_value = NULL ;
	int	value_len ;
	
	int	nret = 0 ;
	
	nret = PUBGetUrlParamPtr( key , & p_value , & value_len ) ;
	if( nret )
		return nret;
	
	if( pp_value )
	{
		(*pp_value) = strndup( p_value , value_len ) ;
		if( (*pp_value) == NULL )
			return -5;
	}
	
	return 0;
}

