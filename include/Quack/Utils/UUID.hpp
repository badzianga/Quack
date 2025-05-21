#ifndef QUACK_UUID_HPP
#define QUACK_UUID_HPP
#include <cstdint>
#include <functional>

class UUID {
public:
    UUID();
    explicit UUID(uint64_t uuid);
    explicit operator uint64_t() const;
    bool operator==(const UUID& other) const;
private:
    uint64_t m_uuid;
};

template<>
struct std::hash<UUID> {
    size_t operator()(const UUID& uuid) const noexcept {
        return std::hash<uint64_t>()(reinterpret_cast<const uint64_t>(&uuid));
    }
};

#endif //QUACK_UUID_HPP
