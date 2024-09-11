// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <memory>
#include <variant>

template <typename T>
class smart_ptr {
    struct vtable_t {
        using destroy_t = void (*)(T*, void*);
        using destructor_t = void (*)(void*);
        destroy_t destroy_;
        destructor_t destructor_;
    };

    template <typename Deleter>
    static void destroy(T* p, void* d) {
        (*static_cast<Deleter*>(d))(p);
    }

    template <typename Deleter>
    static void destructor(void* d) {
        static_cast<Deleter*>(d)->~Deleter();
    }

    template <typename Deleter>
    constexpr static vtable_t vtable = {smart_ptr::template destroy<Deleter>, smart_ptr::template destructor<Deleter>};

    alignas(8) char buf_[16];
    T* p_;
    const vtable_t* vtable_ = nullptr;

   public:
    template <typename Deleter>
    smart_ptr(T* p, Deleter d) : p_(p), vtable_(&vtable<Deleter>) {
        static_assert(sizeof(Deleter) <= sizeof(buf_));
        ::new (static_cast<void*>(buf_)) Deleter(d);
    }
    smart_ptr(T* p) : p_(p), vtable_(&vtable<std::default_delete<T>>) {
        static_assert(sizeof(std::default_delete<T>) <= sizeof(buf_));
        ::new (static_cast<void*>(buf_)) std::default_delete<T>(std::default_delete<T>{});
    }

    ~smart_ptr() {
        this->vtable_->destroy_(p_, buf_);
        this->vtable_->destructor_(buf_);
    }

    T* operator->() { return p_; }
    const T* operator->() const { return p_; }
};

struct data_point {
    uint32_t id;
    std::string name;
    std::variant<std::monostate, bool, float, uint32_t, int32_t, uint16_t, int16_t, uint8_t, int8_t, std::string> value;
};

struct data_point_alt {
    uint16_t id;
    std::string name;
    std::variant<std::monostate, bool, float, uint32_t, int32_t, uint16_t, int16_t, uint8_t, int8_t, std::string> value;
};

struct data_point_deleter_a {
    void operator()(auto* dp) {
        std::puts("data point deleter a");
        delete dp;
    }
};

struct data_point_deleter_b {
    void operator()(auto* dp) {
        std::puts("data point deleter b");
        delete dp;
    }
};

void __attribute__((noinline)) experiment() {
    auto dp1 = smart_ptr<data_point>{new data_point, data_point_deleter_a{}};
    auto dp2 = smart_ptr<data_point>{new data_point, data_point_deleter_a{}};
    auto dp3 = smart_ptr<data_point>{new data_point, data_point_deleter_a{}};
    auto dp4 = smart_ptr<data_point>{new data_point, data_point_deleter_a{}};
}
