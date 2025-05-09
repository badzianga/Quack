function onStart()
    print("Script started!")
end

function onUpdate(dt)
    gameObject.transform.rotation.y = gameObject.transform.rotation.y + 60 * dt
end
