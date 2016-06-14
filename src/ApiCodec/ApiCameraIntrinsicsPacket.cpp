#include "ApiCameraIntrinsicsPacket.hpp"
#include "vitals/CLByteConversion.h"

//=============================================================================
//
ApiCameraIntrinsicsPacket::ApiCameraIntrinsicsPacket( )
{

}

//=============================================================================
//
ApiCameraIntrinsicsPacket::ApiCameraIntrinsicsPacket(
		SourceCamera sourceCamera_,
		double focalLength_,     // Focal length for fisheye correction
		double principalPointX_, // Principal point X coordinate
		double principalPointY_, // Principal point Y coordinate
		double fX_,              // Focal length X axis
		double fY_,             // Focal length Y axis
		double k_1_,             // 1st radial distortion coefficient
		double k_2_,             // 2nd radial distortion coefficient
		double p_1_,             // 1st tangential distortion coefficient
		double p_2_,             // 2nd tangential distortion coefficient
		double k_3_,             // 3rd radial distortion coefficient
		double k_4_,             // 4th radial distortion coefficient
		double k_5_,             // 5th radial distortion coefficient
		double k_6_             // 6th radial distortion coefficient
)
	: 	 sourceCamera{ sourceCamera_ },
		 focalLength{ focalLength_ },
		 principalPointX{ principalPointX_ },
		 principalPointY{ principalPointY_ },
		 fX{ fX_ },
		 fY{ fY_ },
		 k_1{ k_1_ },
		 k_2{ k_2_ },
		 p_1{ p_1_ },
		 p_2{ p_2_ },
		 k_3{ k_3_ },
		 k_4{ k_4_ },
		 k_5{ k_5_ },
		 k_6{ k_6_ }
{

}

//=============================================================================
//
ApiCameraIntrinsicsPacket::~ApiCameraIntrinsicsPacket( )
{

}

//=============================================================================
//
cl_copy::BufferUPtr ApiCameraIntrinsicsPacket::encode()
{
	uint cpt = 0;

	cl_copy::BufferUPtr buffer = cl_copy::unique_buffer( 1 + ( 13 * 8 ) );

	(*buffer)[cpt++] = static_cast<uint8_t>( sourceCamera );

	cl::u8Array< 8 > encodedFocalLength = cl::double_to_u8Array( focalLength );
	cl::u8Array< 8 > encodedPrincipalPointX = cl::double_to_u8Array( principalPointX );
	cl::u8Array< 8 > encodedPrincipalPointY = cl::double_to_u8Array( principalPointY );
	cl::u8Array< 8 > encodedFX = cl::double_to_u8Array( fX );
	cl::u8Array< 8 > encodedFY = cl::double_to_u8Array( fY );
	cl::u8Array< 8 > encodedK_1 = cl::double_to_u8Array( k_1 );
	cl::u8Array< 8 > encodedK_2 = cl::double_to_u8Array( k_2 );
	cl::u8Array< 8 > encodedP_1 = cl::double_to_u8Array( p_1 );
	cl::u8Array< 8 > encodedP_2 = cl::double_to_u8Array( p_2 );
	cl::u8Array< 8 > encodedK_3 = cl::double_to_u8Array( k_3 );
	cl::u8Array< 8 > encodedK_4 = cl::double_to_u8Array( k_4 );
	cl::u8Array< 8 > encodedK_5 = cl::double_to_u8Array( k_5 );
	cl::u8Array< 8 > encodedK_6 = cl::double_to_u8Array( k_6 );

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedFocalLength[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedPrincipalPointX[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedPrincipalPointY[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedFX[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedFY[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedK_1[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedK_2[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedP_1[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedP_2[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedK_3[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedK_4[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedK_5[ i ] );
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		(*buffer)[cpt++] = static_cast<uint8_t>( encodedK_6[ i ] );
	}

	return std::move( getPreparedBuffer( std::move( buffer ), getPacketId() ) );
}

//=============================================================================
//
void ApiCameraIntrinsicsPacket::decode( uint8_t *buffer, uint bufferSize )
{
	util_copy::ignore( bufferSize );

	uint cpt = getStartPayloadIndex();

	sourceCamera = static_cast<SourceCamera>( buffer[ cpt++ ] );

	cl::u8Array< 8 > encodedFocalLength;
	cl::u8Array< 8 > encodedPrincipalPointX;
	cl::u8Array< 8 > encodedPrincipalPointY;
	cl::u8Array< 8 > encodedFX;
	cl::u8Array< 8 > encodedFY;
	cl::u8Array< 8 > encodedK_1;
	cl::u8Array< 8 > encodedK_2;
	cl::u8Array< 8 > encodedP_1;
	cl::u8Array< 8 > encodedP_2;
	cl::u8Array< 8 > encodedK_3;
	cl::u8Array< 8 > encodedK_4;
	cl::u8Array< 8 > encodedK_5;
	cl::u8Array< 8 > encodedK_6;

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedFocalLength[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedPrincipalPointX[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedPrincipalPointY[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedFX[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedFY[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedK_1[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedK_2[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedP_1[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedP_2[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedK_3[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedK_4[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedK_5[ i ] =  buffer[ cpt++ ];
	}

	for( uint i = 0; i < 8 ; i++ )
	{
		encodedK_6[ i ] =  buffer[ cpt++ ];
	}

	focalLength = cl::u8Array_to_double( encodedFocalLength );
	principalPointX = cl::u8Array_to_double( encodedPrincipalPointX );
	principalPointY = cl::u8Array_to_double( encodedPrincipalPointY );
	fX = cl::u8Array_to_double( encodedFX );
	fY = cl::u8Array_to_double( encodedFY );
	k_1 = cl::u8Array_to_double( encodedK_1 );
	k_2 = cl::u8Array_to_double( encodedK_2 );
	p_1 = cl::u8Array_to_double( encodedP_1 );
	p_2 = cl::u8Array_to_double( encodedP_2 );
	k_3 = cl::u8Array_to_double( encodedK_3 );
	k_4 = cl::u8Array_to_double( encodedK_4 );
	k_5 = cl::u8Array_to_double( encodedK_5 );
	k_6 = cl::u8Array_to_double( encodedK_6 );
}

