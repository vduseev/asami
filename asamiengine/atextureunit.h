#ifndef ATEXTUREUNIT_H
#define ATEXTUREUNIT_H

#include "atexture.h"
#include "asampler.h"

#include <QPair>

class ATextureUnit : public QPair<ATexture*, ASampler*>
{
public:
	ATextureUnit();
	explicit ATextureUnit( ATexture* texture, ASampler* sampler );
	
	void setTexture( ATexture* texture ) { first = texture; }
    ATexture* texture() const { return first; }

    void setSampler( ASampler* sampler ) { second = sampler; }
    ASampler* sampler() const { return second; }
};

#endif

