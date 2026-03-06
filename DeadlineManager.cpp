#include "DeadlineManager.h"
#include <chrono>
#include <vector>

using namespace std::chrono;

//
// Created by rchang on 3/5/26.
//
DeadlineManager::DeadlineManager()
{
    deadline.setup_deadline(static_cast<int>(DeadlineType::keep_alive), 500ms);
    deadline.setup_deadline(static_cast<int>(DeadlineType::logging), 50ms);
    deadline.setup_always_contact(static_cast<int>(DeadlineType::keep_alive));
}

bool DeadlineManager::expired(const DeadlineType k) const
{
    return deadline.expired(static_cast<int>(k));
}
