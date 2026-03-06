//
// Created by rchang on 3/5/26.
//

#ifndef DEHM_SERVER_DEADLINEMANAGER_H
#define DEHM_SERVER_DEADLINEMANAGER_H
#include "Deadlines.h"

/// <summary>
/// Maintains the principle deadline.
/// </summary>
class DeadlineManager
{
private:
    DeadlineManager();

    DeadlineManager(const DeadlineManager&) = delete;
    DeadlineManager& operator=(const DeadlineManager&) = delete;

public:
    enum class DeadlineType : int
    {
        cpu,
        monitoring,
        logging,
        keep_alive,
    };

    static DeadlineManager* singleton()
    {
        static DeadlineManager* singleton_instance;
        if (singleton_instance == nullptr)
            singleton_instance = new DeadlineManager();
        return singleton_instance;
    }

    bool contact(DeadlineType k);
    bool expired(DeadlineType k) const;

    /// <summary>
    /// The principle deadline object.
    /// </summary>
    Deadlines<DeadlineType> deadline;
};

#endif //DEHM_SERVER_DEADLINEMANAGER_H
