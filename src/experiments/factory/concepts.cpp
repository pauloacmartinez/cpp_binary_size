// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <array>
#include <cstring>
#include <memory>

#include "random_inputs.h"

template <typename T>
concept ro_storage = requires(T ro_strg, std::string const& str) {
    { ro_strg.store(str) } -> std::convertible_to<bool>;
    { ro_strg.cstr() } -> std::same_as<const char*>;
};

class dynamic_storage {
   private:
    std::string storage{};

   public:
    bool store(std::string const& str) {
        storage = std::move(str);
        return true;
    }

    const char* cstr() { return storage.c_str(); }
};
static_assert(ro_storage<dynamic_storage>);

class fixed_storage {
   private:
    std::array<char, 256> storage;

   public:
    bool store(std::string const& str) {
        if (str.length() > 255) return false;

        std::memcpy(storage.data(), str.data(), str.length());
        storage[str.length()] = '\0';

        return true;
    }

    const char* cstr() { return storage.data(); }
};
static_assert(ro_storage<fixed_storage>);

template <uint8_t type>
auto ro_storage_factory() {
    if constexpr (type == 0) {
        return std::make_shared<dynamic_storage>();
    } else if constexpr (type == 1) {
        return std::make_shared<fixed_storage>();
    } else {
        return nullptr;
    }
};

template <ro_storage T>
void store_and_print(std::shared_ptr<T> const& ro_storage, std::string const& string) {
    if (ro_storage == nullptr) return;
    const auto ret = ro_storage->store(string);
    if (ret) std::puts(ro_storage->cstr());
}

void __attribute__((noinline)) experiment() {
    auto dyn_strg = ro_storage_factory<0>();
    store_and_print(dyn_strg, random_string(32));

    auto fix_strg = ro_storage_factory<1>();
    store_and_print(fix_strg, random_string(32));
}
