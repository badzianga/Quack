function onStart()
    print("Movement script started!")
end

function onUpdate(dt)
    if (Input.isKeyPressed(KeyboardKey.Left)) then
        gameObject.transform.position.x = gameObject.transform.position.x - 12 * dt
    end
    if (Input.isKeyPressed(KeyboardKey.Right)) then
        gameObject.transform.position.x = gameObject.transform.position.x + 12 * dt
    end
    if (Input.isKeyPressed(KeyboardKey.Up)) then
        gameObject.transform.position.z = gameObject.transform.position.z - 12 * dt
    end
    if (Input.isKeyPressed(KeyboardKey.Down)) then
        gameObject.transform.position.z = gameObject.transform.position.z + 12 * dt
    end
end
