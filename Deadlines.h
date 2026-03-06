//
// Created by rchang on 3/5/26.
//
#ifndef DEADLINES_H
#define DEADLINES_H

#include <chrono>
#include <set>
#include <unordered_map>

using namespace std::chrono;

/// <summary>
/// Defines a series of deadlines. A deadline can be reset by a contact.
/// </summary>
class Deadlines
{
    /// <summary>
    /// Defined deadlines.
    /// </summary>
    std::unordered_map<int, system_clock::duration> definitions;

    /// <summary>
    /// Dictionary of last contacts.
    /// </summary>
    std::unordered_map<int, time_point<system_clock>> last_contact;

    /// <summary>
    /// Keys that will always be contacted.
    /// </summary>
    std::pmr::set<int> always_contact;

    bool contact_single(const int key)
    {
        if (expired(key))
        {
            // Thing expired.
            last_contact[key] = system_clock::now();
            return true;
        }

        last_contact[key] = system_clock::now();
        return false;
    }

public:
    Deadlines() = default;

    /// <summary>
    /// Set up the deadline for the key.
    /// </summary>
    /// <param name="key">The key associated with the deadline.</param>
    /// <param name="deadline">The deadline.</param>
    void setup_deadline(const int key, const system_clock::duration deadline)
    {
        definitions[key] = deadline;
    }

    /// <summary>
    /// Flags a key so that when any other key is contacted, the flagged key
    /// will be contacted as well, or disables this behavior if s is false.
    /// </summary>
    /// <param name="key">The key to always be contacted, or to not always be
    /// contacted if s is false.</param>
    /// <param name="s">Controls if the key should always be contacted or
    /// not.</param>
    void setup_always_contact(const int key, const bool s = true)
    {
        if (s)
            always_contact.emplace(key);
        else
            always_contact.erase(key);
    }

    /// <summary>
    /// Contacts the key.
    /// </summary>
    /// <param name="key">The key to contact.</param>
    bool contact(const int& key)
    {
        const bool expired = contact_single(key);

        for (const auto always_contact_key : always_contact)
        {
            contact_single(always_contact_key);
        }

        return expired;
    }

    /// <summary>
    /// Determines if a deadline is expired.
    /// </summary>
    /// <param name="key">The key to check for expiration.</param>
    /// <returns></returns>
    [[nodiscard]] bool expired(const int key) const
    {
        if (last_contact.contains(key))
            return system_clock::now() - last_contact.at(key) > definitions.at(key);
        return true;
    }
};
#endif // DEADLINES_H
