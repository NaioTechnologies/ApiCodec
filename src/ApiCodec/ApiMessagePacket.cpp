#include "ApiMessagePacket.hpp"
#include "vitals/CLByteConversion.h"

//=============================================================================
//
ApiMessagePacket::ApiMessagePacket( )
{

}

//=============================================================================
//
ApiMessagePacket::ApiMessagePacket( API_MESSAGE apiMessage_ )
	: 	apiMessage{ apiMessage_ }
{

}

//=============================================================================
//
ApiMessagePacket::~ApiMessagePacket( )
{

}

//=============================================================================
//
cl::BufferUPtr ApiMessagePacket::encode()
{
	uint cpt = 0;

	cl::BufferUPtr buffer = cl::unique_buffer( 1 );

	(*buffer)[cpt++] = static_cast<uint8_t>( apiMessage );

	return std::move( getPreparedBuffer( std::move( buffer ), getPacketId() ) );
}

//=============================================================================
//
void ApiMessagePacket::decode( uint8_t *buffer, uint bufferSize )
{
	ignore( bufferSize );

	uint cpt = getStartPayloadIndex();

	apiMessage = static_cast< API_MESSAGE >( buffer[ cpt++ ] );
}
