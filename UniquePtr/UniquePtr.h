#pragma once

template <typename Type>
class UniquePtr final {
public:
    explicit UniquePtr(Type* value = nullptr) : value_(value) {}

    UniquePtr(UniquePtr&& ptr) : value_(ptr.value_) {
        ptr.value_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& ptr) {

        if (value_) {
            delete value_;
        }

        if (value_ != ptr.value_) {
            value_ = std::move(ptr.value_);
            ptr.value_ = nullptr;
        }
        return *this;
    }

    Type& operator*() const {
        return *value_;
    }

    Type* operator->() const {
        return value_;
    }

    Type* get() const noexcept {
        return value_;
    }

    operator bool() const noexcept {
        return value_;
    }

    void reset(Type* value) noexcept {
        if (value_)
            delete value_;

        if (value)
            value_ = value;
    }

    Type* release() noexcept {
        Type* old = value_;
        value_ = nullptr;
        return old;
    }

    ~UniquePtr() {
        delete value_;
    }

    UniquePtr(const UniquePtr&) = delete;
    const UniquePtr operator=(const UniquePtr&) = delete;

private:
    Type* value_;
};

template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}