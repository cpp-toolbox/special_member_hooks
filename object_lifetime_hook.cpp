#include "object_lifetime_hook.hpp"

ObjectLifetimeHook::ObjectLifetimeHook(std::function<void()> on_create, std::function<void()> on_destroy)
    : on_destroy_(on_destroy) {
    if (on_create) {
        on_create();
    }
}

ObjectLifetimeHook::~ObjectLifetimeHook() {
    if (on_destroy_) {
        on_destroy_();
    }
}
