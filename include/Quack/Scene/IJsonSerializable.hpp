#ifndef QUACK_I_JSON_SERIALIZABLE_HPP
#define QUACK_I_JSON_SERIALIZABLE_HPP
#include <nlohmann/json_fwd.hpp>

class IJsonSerializable {
public:
    virtual ~IJsonSerializable() = default;

    virtual nlohmann::json serialize() = 0;
    virtual void deserialize(const nlohmann::json& json) = 0;
};

#endif //QUACK_I_JSON_SERIALIZABLE_HPP
