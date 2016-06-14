#include "ApiCameraExtrinsicsPacket.hpp"
#include "vitals/CLByteConversion.h"

//=============================================================================
//
ApiCameraExtrinsicsPacket::ApiCameraExtrinsicsPacket( )
{

}

//=============================================================================
//
ApiCameraExtrinsicsPacket::ApiCameraExtrinsicsPacket( double mat_[], double vec_[] )
{
	for( uint i = 0 ; i < 9 ; i++ )
	{
		mat[ i ] = mat_[ i ];
	}

	for( uint i = 0 ; i < 3 ; i++ )
	{
		vec[ i ] = vec_[ i ];
	}
}

//=============================================================================
//
ApiCameraExtrinsicsPacket::~ApiCameraExtrinsicsPacket( )
{

}

//=============================================================================
//
cl_copy::BufferUPtr ApiCameraExtrinsicsPacket::encode()
{
	uint cpt = 0;

	cl_copy::BufferUPtr buffer = cl_copy::unique_buffer( ( 9 * 8 ) + ( 3 * 8 ) );

	for( uint matIdx = 0 ; matIdx < 9 ; matIdx++ )
	{
		cl::u8Array< 8 > encodedMat = cl::double_to_u8Array( mat[ matIdx ] );

		for( uint byteIdx = 0; byteIdx < 8 ; byteIdx++ )
		{
			(*buffer)[cpt++] = static_cast<uint8_t>( encodedMat[ byteIdx ] );
		}
	}

	for( uint vecIdx = 0 ; vecIdx < 3 ; vecIdx++ )
	{
		cl::u8Array< 8 > encodedVec = cl::double_to_u8Array( vec[ vecIdx ] );

		for( uint byteIdx = 0; byteIdx < 8 ; byteIdx++ )
		{
			(*buffer)[cpt++] = static_cast<uint8_t>( encodedVec[ byteIdx ] );
		}
	}

	return std::move( getPreparedBuffer( std::move( buffer ), getPacketId() ) );
}

//=============================================================================
//
void ApiCameraExtrinsicsPacket::decode( uint8_t *buffer, uint bufferSize )
{
	util_copy::ignore( bufferSize );

	uint cpt = getStartPayloadIndex();

	for( uint matIdx = 0 ; matIdx < 9 ; matIdx++ )
	{
		cl::u8Array< 8 > encodedMat;

		for( uint byteIdx = 0; byteIdx < 8 ; byteIdx++ )
		{
			encodedMat[ byteIdx ] =  buffer[ cpt++ ];
		}

		mat[ matIdx ] = cl::u8Array_to_double( encodedMat );
	}

	for( uint vecIdx = 0 ; vecIdx < 3 ; vecIdx++ )
	{
		cl::u8Array< 8 > encodedVec;

		for( uint byteIdx = 0; byteIdx < 8 ; byteIdx++ )
		{
			encodedVec[ byteIdx ] =  buffer[ cpt++ ];
		}

		vec[ vecIdx ] = cl::u8Array_to_double( encodedVec );
	}
}

