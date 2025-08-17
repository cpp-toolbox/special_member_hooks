#ifndef OBJECT_LIFETIME_HOOK
#define OBJECT_LIFETIME_HOOK
#include <functional>

class ObjectLifetimeHook {
  public:
    explicit ObjectLifetimeHook(std::function<void()> on_create, std::function<void()> on_destroy);

    ~ObjectLifetimeHook();

  private:
    std::function<void()> on_destroy_;
};

#endif // OBJECT_LIFETIME_HOOK
