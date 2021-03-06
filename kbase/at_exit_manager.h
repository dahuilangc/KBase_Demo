/*
 @ Kingsley Chen
*/

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef KBASE_AT_EXIT_H_
#define KBASE_AT_EXIT_H_

#include <functional>
#include <mutex>
#include <stack>

namespace kbase {

class AtExitManager {
public:
    typedef std::function<void(void*)> AtExitCallbackType;    

    AtExitManager();

    ~AtExitManager();

    static void RegisterCallback(const AtExitCallbackType& callback, void* param);
    
    static void ProcessCallbackNow();

    AtExitManager(const AtExitManager&) = delete;

    AtExitManager& operator=(const AtExitManager&) = delete;

private:
    std::mutex lock_;
    std::stack<std::function<void()>> callback_stack_;
    AtExitManager* next_at_exit_manager_;
};

}   // namespace kbase

#endif  // KBASE_AT_EXIT_H_