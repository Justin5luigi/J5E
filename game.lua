Assets =
    {
        [0] =
            { type = "texture", id = "test", file = "./assets/tank-panther-right.png" }
    }

Existents =
    {
        [0] =
            {
                elements =
                    {
                        {type = "TransformElement", xpos = 10, ypos = 10, xscale = 1, yscale = 1, rotation = 0},
                        {type = "RigidBodyElement", xspd = 30, yspd = 0},
                        {type = "SpriteElement", assetID = "test", w = 32, h = 32},
                        {type = "ColliderElement", w = 32, h = 32},
                        {type = "ScriptElement", scriptPath = "./testscript.lua"}
                    }
            },
            {
                elements =
                    {
                        {type = "TransformElement", xpos = 800, ypos = 10, xscale = 1, yscale = 1, rotation = 0},
                        {type = "RigidBodyElement", xspd = 0, yspd = 0},
                        {type = "SpriteElement", assetID = "test", w = 32, h = 32},
                        {type = "ColliderElement", w = 32, h = 32}
                    }
            }
    }
