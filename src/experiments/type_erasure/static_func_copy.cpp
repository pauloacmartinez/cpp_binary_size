// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <memory>
#include <variant>

template <typename T>
class smart_ptr {
    template <typename Deleter>
    static void invoke_destroy(T* p, void* d) {
        (*static_cast<Deleter*>(d))(p);
    }

    template <typename Deleter>
    static void* invoke_clone(void* d) {
        return ::new Deleter(*static_cast<Deleter*>(d));
    }

    T* p_;
    void* d_;
    void (*destroy_)(T*, void*);
    void* (*clone_)(void*);

   public:
    template <typename Deleter>
    smart_ptr(T* p, Deleter d) : p_(p), d_(::new Deleter(d)), destroy_(invoke_destroy<Deleter>), clone_(invoke_clone<Deleter>) {}
    smart_ptr(T* p)
        : p_(p),
          d_(::new std::default_delete<T>(std::default_delete<T>{})),
          destroy_(invoke_destroy<std::default_delete<T>>),
          clone_(invoke_clone<std::default_delete<T>>) {}

    smart_ptr(const smart_ptr<T>& sp) : p_(::new T(*sp.p_)), d_(sp.clone_(sp.d_)), destroy_(sp.destroy_), clone_(sp.clone_) {}
    smart_ptr& operator=(smart_ptr<T> const& sp) = delete;

    ~smart_ptr() { this->destroy_(p_, d_); }

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