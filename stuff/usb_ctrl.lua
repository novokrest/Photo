--[[
@title USB Controller

@param t Shutter Adjust (stops)
@default t 1

--]]

require("drawings")

tv_default=576

function usb_wait(i)
   print("USB wait",i)
   repeat
      a = get_usb_power(1)
      sleep(50)
   until a == i
end

function usb_remote_state(i)
    if (i== 0 ) then
        set_config_value(121, 0)
        print("turning remote off")
    else
        set_config_value(121, 1)
        print("turning remote on")
    end
end

function switch_mode( m )   -- change between shooting and playback mode
    if ( m == 1 ) then
        if ( get_mode() == false ) then
            print("switching to record mode")
            set_record(1)
            while ( get_mode() == false ) do sleep(100) end
        end
    else
        if ( get_mode() == true) then
           print("switching to playback mode")
           set_record(0)
           while ( get_mode() == true ) do sleep(100) end
        end
    end
end

function pline(line, message)     -- print line function
    if      ( line == 1 ) then fg = 271 bg=265
    elseif  ( line == 5 ) then fg = 258 bg=265
    else fg = 265 bg=258 end
    draw_string( 32, line*16, string.sub(message.."                          ",0,34), fg, bg)
 end

function tv2seconds(tv_val)
     local i = 1
     local tv_str = {"???","64","50","40","32","25","20","16","12","10","8","6",
    "5","4","3.2","2.5","2","1.6","1.3","1.0","0.8","0.6","0.5","0.4",
    "0.3","1/4","1/5","1/6","1/8","1/10","1/13","1/15","1/20","1/25",
    "1/30","1/40","1/50","1/60","1/80","1/100","1/125","1/160","1/200",
    "1/250","1/320","1/400","1/500","1/640","1/800","1/1000","1/1250",
    "1/1600","1/2000","off"  }
     local tv_ref = {
     -576, -544, -512, -480, -448, -416, -384, -352, -320, -288, -256, -224, -192, -160, -128, -96, -64, -32, 0,
     32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512, 544, 576, 608, 640, 672, 704,
     736, 768, 800, 832, 864, 896, 928, 960, 992, 1021, 1053, 1080 }
     while (i <= #tv_ref) and (tv_val > tv_ref[i]-1) do i=i+1 end
     return tv_str[i]
end

function show_status_box(msg)
    local st="        "
    pline(1,string.format("     USB Remote Shooter"))
    pline(2,st)
    pline(3,msg)
    pline(4,st)
    pline(5,string.format("       Press MENU to Exit"))
end

set_console_layout(1, 1, 44, 7)
usb_remote_state(1)
switch_mode(1)
count=0
tv_setpoint=tv_default
print("USB Control Started")

repeat
   -- wait for USB power to be applied
   pwidth=0
   repeat
      pwidth=pwidth+50
      sleep(50)
      a = get_usb_power(1)
   until (a == 1) or (pwidth>500)
   if ( a==0) then   -- more than 500 mSec with no USB pwer
       if(pcount ==1) then 
          print("reset")
          tv_setpoint=tv_default
       elseif ( pcount == 2) then
          print("increase tv")
          tv_setpoint=tv_setpoint+96*t
       elseif ( pcount == 3 ) then 
          print("decrease tv")
          tv_setpoint=tv_setpoint-96*t
       end
       show_status_box(string.format("      Tv=%s ", tv2seconds(tv_setpoint)))
       pcount = 0
   else             -- USB power applied
      pwidth=0
      repeat        -- wait for 500 mSec or until USB power goes away
         pwidth=pwidth+50
         sleep(50)
         a = get_usb_power(1)
      until (a == 0) or (pwidth>500)

      if (pwidth>500) then 
        --start shooting sequence if USB power on for more than 500 mSec
        pcount=0
        set_tv96(tv_setpoint)
        print("shoot half")
        press("shoot_half")
        repeat sleep(50) until get_shooting() == true
        repeat        -- wait until USB power goes away
           show_status_box("     WAITING TO SHOOT ")
           sleep(20)
           a = get_usb_power(1)
        until (a == 0) 
        print("shoot full")
        press("shoot_full")
        sleep(500)
        release("shoot_full")
        repeat sleep(50) until get_shooting() == false   
        release("shoot_half")
     else
        -- increment pulse count in USB power on for less than 500 mSec
        pcount=pcount+1
        print("pcount=",pcount)
     end
   end

until ( is_key("set")  or is_key("menu") )

print("key pressed")
usb_remote_state(0)
switch_mode(0)

