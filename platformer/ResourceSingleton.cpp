#include "ResourceSingleton.h"

ResourceSingleton ResourceSingleton::singleton;

void ResourceSingleton::Initialize()
{
	if (!singleton.res_)
	{
		singleton.res_ = std::make_unique<oxygine::Resources>();
		singleton.res_->loadXML("resources/resources.xml");
	}
}

const oxygine::Resources& ResourceSingleton::GetRes()
{
	Initialize();
	return *singleton.res_.get();
}