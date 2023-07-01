    template<typename Traits>
    Myos<T>& operator<<(Traits&& value)noexcept {
        std::cout<<"A";
        mys<<std::forward<Traits>(value);
        return *this;
    }