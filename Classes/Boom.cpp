#include "Boom.h"

Boom *Boom::create(const std::string &t){
	
	Boom *boom = new (std::nothrow) Boom();
	if (boom && boom->initWithFile(t)){
		boom->autorelease();
		return boom;
	}
	CC_SAFE_DELETE(boom);
	return nullptr;

}