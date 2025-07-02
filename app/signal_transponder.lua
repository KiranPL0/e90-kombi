local socket = require('shared/socket')
local udp = socket.udp()

local speed
local rpm
local abs
local gear
local fuel
local engine
local tclevel
local left_signals
local right_signals
local hazard_signals
local high_beams
local handbrake
local headlight

local timestamp_time = socket.gettime()*1000

udp:settimeout(1)
udp:setpeername("127.0.0.1", 6969) 

print("Script loaded!")

function script.update(dt)
    left_signal = ac.getCar().turningLeftLights
    right_signal = ac.getCar().turningRightLights
    hazard_signal = ac.getCar().hazardLights

        speed = ac.getCar().speedKmh
    rpm = ac.getCar().rpm
    gear = ac.getCar().gear -- -1 = Reverse; 0 = Neutral, 1 = 1st, ..
    fuel = (ac.getCar().fuel/ac.getCar().maxFuel) * 100
    abs = ac.getCar().absInAction
    tclevel = ac.getCar().tractionControlMode
    handbrake = ac.getCar().handbrake
    headlight = ac.getCar().headlightsActive
    if rpm > 100 then
        engine = true
    else
        engine = false
    end
    if ac.getCar().headlightsActive and not ac.getCar().lowBeams then
        high_beams = true
    else
        high_beams = false
    end
    if ((socket.gettime()*1000)- timestamp_time) > 100 then
        data_send()
        timestamp_time = socket.gettime()*1000
        -- print(tostring(speed).."$"..tostring(rpm).."$"..tostring(abs).."$"..tostring(gear).."$"..tostring(fuel).."$"..tostring(engine).."$"..tostring(tclevel).."$"..tostring(left_signal).."$"..tostring(right_signal).."$"..tostring(hazard_signal).."$"..tostring(high_beams).."$"..tostring(handbrake).."$"..tostring(headlight))
    
end

end

function script.windowMain(dt)
    ui.text("Left Signal Status: " .. tostring(left_signal))
    ui.text("Right Signal Status: " .. tostring(right_signal))
    ui.text("Hazard Lights Status: " .. tostring(hazard_signal))

    ui.text("Speed: ".. tostring(speed))
    ui.text("RPM: ".. tostring(rpm))
    ui.text("abs: ".. tostring(abs))
    ui.text("GEAR: ".. tostring(gear))
    ui.text("Fuel: ".. tostring(fuel))
    ui.text("Engine: ".. tostring(engine))
    ui.text("Traction: ".. tostring(tclevel))
    ui.text("Headlights: ".. tostring(ac.getCar().headlightsActive))
    ui.text("Low Beams: ".. tostring(ac.getCar().lowBeams))
    ui.text("High Beams: ".. tostring(high_beams))
    ui.text("Handbrake: ".. tostring(handbrake))

    ui.text(ac.getCar())

    -- data_send()

    
end

function resetUDP()
    print("resetting UDP socket")
    udp:close()
    udp = socket.udp()
    udp:settimeout(1)
    udp:setpeername("127.0.0.1", 6969)
end
function data_send()
    local success, err = udp:send(tostring(speed).."$"..tostring(rpm).."$"..tostring(abs).."$"..tostring(gear).."$"..tostring(fuel).."$"..tostring(engine).."$"..tostring(tclevel).."$"..tostring(left_signal).."$"..tostring(right_signal).."$"..tostring(hazard_signal).."$"..tostring(high_beams).."$"..tostring(handbrake).."$"..tostring(headlight))
    if not success then
        print("UDP send failed!", err or "unknown")
        resetUDP()
    end
end

function script.onStop()
    udp:close()
end


