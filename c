local Noclip = nil
local Clip = nil

function clip()
    if Noclip then
        Noclip:Disconnect()
    end
    Clip = true
    
    if game.Players.LocalPlayer.Character ~= nil then
        for _,v in pairs(game.Players.LocalPlayer.Character:GetDescendants()) do
            if v:IsA('BasePart') and v.Name ~= floatName then
                v.CanCollide = true
            end
        end
    end
end

clip() -- 클립 활성화
