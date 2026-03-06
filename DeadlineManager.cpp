#include "DeadlineManager.h"
#include <chrono>
#include <vector>

using namespace std::chrono;

//
// Created by rchang on 3/5/26.
//
DeadlineManager::DeadlineManager()
{
    deadline.setup_deadline(DeadlineType::keep_alive, 500ms);
    deadline.setup_deadline(DeadlineType::monitoring, 20ms);
    deadline.setup_deadline(DeadlineType::logging, 50ms);
    deadline.setup_always_contact(DeadlineType::keep_alive);
}

bool DeadlineManager::contact(const DeadlineType k)
{
    return deadline.contact(k);
}

bool DeadlineManager::expired(const DeadlineType k) const
{
    return deadline.expired(k);
}
