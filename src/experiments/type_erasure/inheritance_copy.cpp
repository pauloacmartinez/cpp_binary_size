// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <memory>
#include <variant>

template <typename T>
class smart_ptr {
    struct destroy_base {
        virtual void destroy_obj(T*) = 0;
        virtual destroy_base* clone() const = 0;
        virtual ~destroy_base() {}
    };

    template <typename Deleter>
    struct destroy : public destroy_base {
        destroy(Deleter d) : del(d) {}
        void destroy_obj(T* p) override { del(p); }
        destroy_base* clone() const { return ::new destroy<Deleter>(*this); }
        Deleter del;
    };

    T* p_;
    destroy_base* d_;

   public:
    template <typename Deleter>
    smart_ptr(T* p, Deleter d) : p_(p), d_(::new destroy<Deleter>(d)) {}
    smart_ptr(T* p) : p_(p), d_(::new destroy<std::default_delete<T>>(std::default_delete<T>{})) {}

    smart_ptr(const smart_ptr<T>& sp) : p_(::new T(*sp.p_)), d_(sp.d_->clone()) {}
    smart_ptr& operator=(smart_ptr<T> const& sp) = delete;

    ~smart_ptr() {
        d_->destroy_obj(p_);
        delete d_;
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
    void operator()(data_point* dp) {
        std::puts("data point deleter");
        delete dp;
    }
};

void __attribute__((noinline)) experiment() {
    auto dp = smart_ptr<data_point>{new data_point, data_point_deleter{}};
    auto dp_copy = dp;
}
