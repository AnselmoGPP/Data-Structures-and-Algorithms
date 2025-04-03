#include "object_pool.hpp"


Resource::Resource() { value = 0; }

void Resource::reset() { value = 0; }

int Resource::getValue() { return value; }

void Resource::setValue(int number) { value = number; }

ObjectPool::ObjectPool() { }

ObjectPool* ObjectPool::getInstance()
{
    if (instance == nullptr)
        instance = new ObjectPool;

    return instance;
}

Resource* ObjectPool::getResource()
{
    if (resources.empty())
        return new Resource;
    else
    {
        Resource* resource = resources.front();
        resources.pop();
        return resource;
    }
}

void ObjectPool::returnResource(Resource* object)
{
    object->reset();
    resources.push(object);
}

ObjectPool* ObjectPool::instance = 0;