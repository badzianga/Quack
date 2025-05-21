#include "Quack/Utils/UUID.hpp"
#include <random>

static std::random_device rd;
static std::mt19937_64 gen(rd());
static std::uniform_int_distribution<uint64_t> dist;

UUID::UUID() : m_uuid(dist(gen)) {}

UUID::UUID(uint64_t uuid) : m_uuid(uuid) {}

UUID::UUID(UUID::Internal uuid) : m_uuid(static_cast<uint64_t>(uuid)) {}

UUID::operator uint64_t() const {
    return m_uuid;
}

bool UUID::operator==(const UUID& other) const {
    return m_uuid == other.m_uuid;
}
