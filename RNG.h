//
// Created by rchang on 3/7/26.
//

#ifndef DEHM_SERVER_RNG_H
#define DEHM_SERVER_RNG_H
#include <random>

class RNG
{
private:
    RNG()
    {
        std::random_device rd;
        engine = std::mt19937_64{rd()};
    }

public:
    RNG(const RNG&) = delete;
    RNG& operator=(const RNG&) = delete;

    std::mt19937_64 engine;

    static RNG* singleton()
    {
        static RNG* singleton_instance;
        if (singleton_instance == nullptr)
            singleton_instance = new RNG();
        return singleton_instance;
    }
    
    unsigned long operator()()
    {
        return engine();
    }
    
    static unsigned long get()
    {
        return (*singleton())();
    }
};
#endif //DEHM_SERVER_RNG_H
