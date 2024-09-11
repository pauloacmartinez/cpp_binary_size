// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <memory>
#include <variant>

template <typename T>
class smart_ptr {
    struct vtable_t {
        using destroy_t = void (*)(T*, void*);
        using destructor_t = void (*)(void*);
        using clone_t = void* (*)(void*);
        destroy_t destroy_;
        destructor_t destructor_;
        clone_t clone_;
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
    static void* clone(void* d) {
        return ::new Deleter(*static_cast<Deleter*>(d));
    }

    template <typename Deleter>
    constexpr static vtable_t vtable = {smart_ptr::template destroy<Deleter>, smart_ptr::template destructor<Deleter>,
                                        smart_ptr::template clone<Deleter>};

    T* p_;
    void* d_;
    const vtable_t* vtable_ = nullptr;

   public:
    template <typename Deleter>
    smart_ptr(T* p, Deleter d) : p_(p), d_(new Deleter(d)), vtable_(&vtable<Deleter>) {}
    smart_ptr(T* p) : p_(p), d_(new std::default_delete<T>(std::default_delete<T>{})), vtable_(&vtable<std::default_delete<T>>) {}

    smart_ptr(const smart_ptr<T>& sp) : p_(::new T(*sp.p_)), d_(sp.vtable_->clone_(sp.d_)), vtable_(sp.vtable_) {}
    smart_ptr& operator=(smart_ptr<T> const& sp) = delete;

    ~smart_ptr() {
        this->vtable_->destroy_(p_, d_);
        this->vtable_->destructor_(d_);
    }

    T* operator->() { return p_; }
    const T* operator->() const { return p_; }
};

struct data_point {
    uint32_t id;
    std::string name;
    std::variant<std::monostate, bool, float, uint32_t, int32_t, uint16_t, int16_t, uint8_t, int8_t, std::string> value;
};

struct data_point_deleter {
    void operator()(auto* dp) {
        std::puts("data point deleter");
        delete dp;
    }
};

void __attribute__((noinline)) experiment() {
    auto dp = smart_ptr<data_point>{new data_point, data_point_deleter{}};
    auto dp_copy = dp;
}
