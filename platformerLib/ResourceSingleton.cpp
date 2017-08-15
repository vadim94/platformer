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

void ResourceSingleton::UnInitialize()
{
    singleton.res_->free();
}

const oxygine::Resources& ResourceSingleton::GetRes()
{
    Initialize();
    return *singleton.res_.get();
}