// Copyright (c) 2024 Paulo Martinez
// Licensed under the MIT License, see LICENSE file.

#include <array>
#include <cstring>
#include <memory>

#include "random_inputs.h"

struct ro_storage {
    virtual bool store(std::string const& strr) = 0;
    virtual const char* cstr() = 0;
    virtual ~ro_storage() = default;
};

class dynamic_storage : public ro_storage {
   private:
    std::string storage{};

   public:
    bool store(std::string const& str) override {
        storage = std::move(str);
        return true;
    }

    const char* cstr() override { return storage.c_str(); }
};

class fixed_storage : public ro_storage {
   private:
    std::array<char, 256> storage;

   public:
    bool store(std::string const& str) override {
        if (str.length() > 255) return false;

        std::memcpy(storage.data(), str.data(), str.length());
        storage[str.length()] = '\0';

        return true;
    }

    const char* cstr() override { return storage.data(); }
};

std::shared_ptr<ro_storage> ro_storage_factory(uint8_t type) {
    if (type == 0) {
        return std::make_shared<dynamic_storage>();
    } else if (type == 1) {
        return std::make_shared<fixed_storage>();
    } else {
        return {nullptr};
    }
};

void store_and_print(std::shared_ptr<ro_storage> const& ro_storage, std::string const& string) {
    if (ro_storage == nullptr) return;
    const auto ret = ro_storage->store(string);
    if (ret) std::puts(ro_storage->cstr());
}

void __attribute__((noinline)) experiment() {
    auto dyn_strg = ro_storage_factory(0);
    store_and_print(dyn_strg, random_string(32));

    auto fix_strg = ro_storage_factory(1);
    store_and_print(fix_strg, random_string(32));
}
