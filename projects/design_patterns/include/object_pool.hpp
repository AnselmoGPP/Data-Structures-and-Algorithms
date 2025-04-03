#ifndef OBJECT_POOL_HPP
#define OBJECT_POOL_HPP

#include <string>
#include <iostream>
#include <queue>

/*
    Object pool:
    Avoid creating new instances of a class by reusing them.
    This can improve performance. It's most effective when initialization cost is high, instantiation rate is high, and number of instances in use at any one time is low.
    The ReusablePool is a singleton to keep all unused Reusable objects in the same pool so that they can be managed by one coherent policy.
    At request, if pool is empty, a new element is created and taken; otherwise, one from the pool is taken. At return, the element is reset and stored in pool.
*/

class Resource
{
    int value;
public:
    Resource();

    void reset();
    int getValue();
    void setValue(int number);
};

/// This class is a singleton.
class ObjectPool
{
private:
    ObjectPool();

    static ObjectPool* instance;

    std::queue<Resource*> resources;   // FIFO queue

public:
    /// Access to singleton instance
    static ObjectPool* getInstance();

    /// Get a resource instance. New resource will be created if all resources are in use.
    Resource* getResource();

    /// Initialize resource back to default settings and return it to the pool.
    void returnResource(Resource* object);
};

ObjectPool* ObjectPool::instance = 0;

void test_object_pool()
{
    ObjectPool* pool = ObjectPool::getInstance();
    Resource* one;
    Resource* two;

    // Resources creation
    one = pool->getResource();
    one->setValue(10);
    two = pool->getResource();
    two->setValue(20);
    std::cout << "one.value = " << one->getValue() << std::endl;
    std::cout << "two.value = " << two->getValue() << std::endl;
    pool->returnResource(one);
    pool->returnResource(two);

    // Resources reused
    one = pool->getResource();
    two = pool->getResource();
    std::cout << "one.value = " << one->getValue() << std::endl;
    std::cout << "two.value = " << two->getValue() << std::endl;
}

#endif