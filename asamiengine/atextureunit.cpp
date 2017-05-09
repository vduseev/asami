#include "atextureunit.h"

ATextureUnit::ATextureUnit()
	: QPair<ATexture*, ASampler*>( new ATexture(), new ASampler() )
{
}

ATextureUnit::ATextureUnit( ATexture* texture, ASampler* sampler )
	: QPair<ATexture*, ASampler*>( texture, sampler )
{
}