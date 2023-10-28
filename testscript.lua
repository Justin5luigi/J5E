function Update(delta)
    if IsKeyPressed(this, "R") then
        SetVelocity(this, 0, -150)
    end

    if IsKeyPressed(this, "O") then
        SetVelocity(this, 150, 0)
    end

    if IsKeyPressed(this, "Q") then
        SetVelocity(this, 0, 150)
    end

    if IsKeyPressed(this, "P") then
        SetVelocity(this, -150, 0)
    end

end

function OnCollision(other)
        local posx = math.random(1, 800)
        local posy = math.random(1, 800)
        SetPosition(other, posx, posy)
        Log("LUA, new pos = (" .. posx .. "," .. posy .. ")")
    end

--ROQP
--R = up
--O = right
--Q = down
--P = left
