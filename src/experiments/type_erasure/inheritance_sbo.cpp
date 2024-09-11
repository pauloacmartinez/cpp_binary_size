// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <memory>
#include <variant>

template <typename T>
class smart_ptr {
    struct destroy_base {
        virtual void destroy_obj(T*) = 0;
        virtual ~destroy_base() {}
    };

    template <typename Deleter>
    struct destroy : public destroy_base {
        destroy(Deleter d) : del(d) {}
        void destroy_obj(T* p) override { del(p); }
        Deleter del;
    };

    T* p_;
    destroy_base* d_;

    alignas(8) char buf_[16];

   public:
    template <typename Deleter>
    smart_ptr(T* p, Deleter d) : p_(p) {
        static_assert(sizeof(Deleter) <= sizeof(buf_));
        d_ = ::new (buf_) destroy<Deleter>(d);
    }
    smart_ptr(T* p) : p_(p) {
        static_assert(sizeof(std::default_delete<T>) <= sizeof(buf_));
        d_ = ::new (buf_) destroy<std::default_delete<T>>(std::default_delete<T>{});
    }

    ~smart_ptr() {
        d_->destroy_obj(p_);
        d_->~destroy_base();
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
