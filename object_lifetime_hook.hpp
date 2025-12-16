#ifndef SPECIAL_MEMBER_HOOKS
#define SPECIAL_MEMBER_HOOKS

#include "sbpt_generated_includes.hpp"

#include <functional>
#include <iostream>

/**
 * @brief Allows hooking into the special member functions of a class.
 *
 * This class provides a set of callback hooks for the following C++ special member functions:
 * - Default constructor
 * - Copy constructor
 * - Move constructor
 * - Copy assignment operator
 * - Move assignment operator
 * - Destructor
 *
 * Each hook is represented as a std::function<void()> member, e.g. `on_construct` for the
 * default constructor, `on_destroy` for the destructor, etc. Whenever the corresponding
 * special function is called on this object, the assigned callback (if any) will be invoked.
 *
 * The main purpose of this class is to allow external systems to react to the lifetime
 * events of objects. For example, a system might want to:
 * - Log or track object constructions, copies, moves, or destruction.
 * - Perform metrics or profiling based on object lifetime events.
 * - Trigger other dependent logic in response to an object's lifecycle changes.
 *
 * @note Hooks are copied or moved along with the object, so the behavior persists through
 *       copy and move operations. This ensures that the callbacks remain attached to the
 *       object even after it is copied or moved.
 *
 * @warning Be careful when modifying objects inside hooks; since hooks can be invoked
 *          during construction, assignment, or destruction, modifying certain members
 *          may lead to undefined behavior.
 */
struct SpecialMemberHooks {
    std::function<void()> on_construct;
    std::function<void()> on_copy_construct;
    std::function<void()> on_move_construct;
    std::function<void()> on_copy_assign;
    std::function<void()> on_move_assign;
    std::function<void()> on_destroy;

    SpecialMemberHooks() {
        global_logger->debug("SpecialMemberHooks: default constructor called");
        if (on_construct)
            on_construct();
    }

    SpecialMemberHooks(const SpecialMemberHooks &other)
        : on_construct(other.on_construct), on_copy_construct(other.on_copy_construct),
          on_move_construct(other.on_move_construct), on_copy_assign(other.on_copy_assign),
          on_move_assign(other.on_move_assign), on_destroy(other.on_destroy) {
        global_logger->debug("SpecialMemberHooks: copy constructor called");
        if (on_copy_construct)
            on_copy_construct();
    }

    SpecialMemberHooks(SpecialMemberHooks &&other) noexcept
        : on_construct(std::move(other.on_construct)), on_copy_construct(std::move(other.on_copy_construct)),
          on_move_construct(std::move(other.on_move_construct)), on_copy_assign(std::move(other.on_copy_assign)),
          on_move_assign(std::move(other.on_move_assign)), on_destroy(std::move(other.on_destroy)) {
        global_logger->debug("SpecialMemberHooks: move constructor called");
        if (on_move_construct)
            on_move_construct();
    }

    SpecialMemberHooks &operator=(const SpecialMemberHooks &other) {
        global_logger->debug("SpecialMemberHooks: copy assignment called");
        if (this != &other) {
            on_construct = other.on_construct;
            on_copy_construct = other.on_copy_construct;
            on_move_construct = other.on_move_construct;
            on_copy_assign = other.on_copy_assign;
            on_move_assign = other.on_move_assign;
            on_destroy = other.on_destroy;

            if (on_copy_assign)
                on_copy_assign();
        }
        return *this;
    }

    SpecialMemberHooks &operator=(SpecialMemberHooks &&other) noexcept {
        global_logger->debug("SpecialMemberHooks: move assignment called");
        if (this != &other) {
            on_construct = std::move(other.on_construct);
            on_copy_construct = std::move(other.on_copy_construct);
            on_move_construct = std::move(other.on_move_construct);
            on_copy_assign = std::move(other.on_copy_assign);
            on_move_assign = std::move(other.on_move_assign);
            on_destroy = std::move(other.on_destroy);

            if (on_move_assign)
                on_move_assign();
        }
        return *this;
    }

    ~SpecialMemberHooks() {
        global_logger->debug("SpecialMemberHooks: destructor called");
        if (on_destroy)
            on_destroy();
    }
};

#endif // SPECIAL_MEMBER_HOOKS
