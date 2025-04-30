#ifndef QUACK_COMPONENT_HPP
#define QUACK_COMPONENT_HPP

class GameObject;

/**
 * @brief Base class for all components.
 *
 * A component adds behavior or data to a GameObject.
 * Derived classes implements start() and update().
 */
class Component {
public:
    /**
     * @brief Virtual destructor.
     *
     * Ensures proper cleanup in derived component classes.
     */
    virtual ~Component() = default;

    /**
     * @brief Called once when the component is initialized.
     *
     * Called by the scene after the GameObject is created.
     */
    virtual void start() = 0;

    /**
     * @brief Called once per frame.
     *
     * Used to implement per-frame logic or behavior.
     * Called by the scene.
     */
    virtual void update() = 0;

    /**
     * @brief Pointer to the owning %GameObject.
     *
     * Set automatically when the component is added.
     */
    GameObject* gameObject = nullptr;

    /// Indicate whether the component is enabled (updated every frame)/
    bool enabled = true;
};

#endif //QUACK_COMPONENT_HPP
