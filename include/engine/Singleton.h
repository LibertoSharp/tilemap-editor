#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>

template <typename ClassType>
class Singleton {
public:
    Singleton(ClassType* instance) {
        if (!Singleton<ClassType>::instance)
        Singleton<ClassType>::instance = instance;
    }

    static ClassType* getInstance() {
        return instance;
    }

private:
    static ClassType* instance;
};

template<typename ClassType>
ClassType* Singleton<ClassType>::instance = nullptr;


#endif //SINGLETON_H
