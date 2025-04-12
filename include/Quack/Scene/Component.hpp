#ifndef QUACK_COMPONENT_HPP
#define QUACK_COMPONENT_HPP

class GameObject;

class Component {
public:
    GameObject* gameObject = nullptr;
    bool enabled = true;

    virtual ~Component() = default;
    virtual void start() = 0;
    virtual void update() = 0;
};

#endif //QUACK_COMPONENT_HPP
