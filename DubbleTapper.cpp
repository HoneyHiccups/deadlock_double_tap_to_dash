#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <ctime>
#include <stdio.h>
#include <unistd.h>
#include <X11/extensions/XTest.h>

using namespace std;

enum keycode{
w = 25,
a = 38,
s = 39,
d = 40,
null =0
};
struct key_press_time_struc{
    keycode key = keycode::null;
    double time =0;
};
unsigned char lastkeypress = 0;

double delta = 0;
double running_time=0;
double doubletaptimmer=0.22;
double runingtime_press_timer_target =0;
double event_q_time = 0;
timespec time1;
timespec time2;
char keybord_state[32];

bool w_pressed = false;
bool a_pressed = false;
bool s_pressed = false;
bool d_pressed = false;

bool w_just_pressed = false;
bool a_just_pressed = false;
bool s_just_pressed = false;
bool d_just_pressed = false;

bool w_just_realsed = false;
bool a_just_realsed = false;
bool s_just_realsed = false;
bool d_just_realsed = false;

bool get_keystate(unsigned char keycode){
    return bool((keybord_state[keycode/8] >> (keycode%8)) & 1);
}
Display* disp_server = nullptr;
void set_pressed_bools();
void clean_bools();
key_press_time_struc handle_pressed();
void event_duble_tap();

int main(){

    char lastkey  = 0;
    disp_server = XOpenDisplay(NULL);
    if(disp_server == nullptr){
        printf("Failed to get display sever");
        return -1;
    }
    key_press_time_struc press;
    key_press_time_struc lastpress;

    while(true == true){
        XQueryKeymap(disp_server, keybord_state);
        set_pressed_bools();
        
        press = handle_pressed();
        if(press.key != null){
            if(lastpress.key == press.key){
                if((press.time-lastpress.time) < doubletaptimmer){
                    if(running_time>runingtime_press_timer_target){
                        event_q_time =running_time + 0.02;
                    }
                    press.time =running_time;
                    press.key = keycode::null;
                }
            }
        }

        if (event_q_time <= running_time){
            event_duble_tap();
            event_q_time = 9999999999999.9;
        }

        if(press.key != keycode::null){
            lastpress = press;  
        }
        
        clean_bools();
        delta = 0.003;
        running_time = running_time+delta;
        usleep(3000);
    } 
    return 0;
}

void event_duble_tap(){
    if(w_pressed == true && s_pressed == true){
        return;
    } // these stop from dashing when opsite keys are pressed// you can still do the dash but u have to switch to new key press// this makes things work better in deadlock
    if(a_pressed == true && d_pressed ==true){
        return;
    }
    runingtime_press_timer_target = running_time+(doubletaptimmer*1.7);
    printf("sprint button at running time of:: %f \n", running_time);
    XTestFakeKeyEvent(disp_server, 51, true, 0);
    XTestFakeKeyEvent(disp_server, 51, false, 0);
    XFlush(disp_server);
}

key_press_time_struc handle_pressed(){
    key_press_time_struc out;
    unsigned char _lastkeypress = 0;
    out.key = keycode::null;
    if(w_just_pressed == true){
        _lastkeypress = keycode::w;
        out.key = keycode::w;
    }
    if(a_just_pressed == true){
        _lastkeypress = keycode::a;
        out.key = keycode::a;
    }
    if(s_just_pressed == true){
        _lastkeypress = keycode::s;
        out.key = keycode::s;
    }
    if(d_just_pressed == true){
        _lastkeypress = keycode::d;
        out.key = keycode::d;
    }
    out.time = running_time;
    return out;
    
}

void clean_bools(){
    w_just_realsed = false;
    a_just_realsed = false;
    s_just_realsed = false;
    d_just_realsed = false;

    w_just_pressed = false;
    a_just_pressed = false;
    s_just_pressed = false;
    d_just_pressed = false;
}
void set_pressed_bools(){

    if(get_keystate(keycode::w) == true){
        if(w_pressed == false){
           w_pressed = true;
           w_just_pressed = true;
        }
        w_pressed = true;
    }else{
        //w not pressed
        if(w_pressed == true){
           w_pressed = false;
           w_just_realsed = true;
        }
    }

    if(get_keystate(keycode::a) == true){
        if(a_pressed == false){
           a_pressed = true;
           a_just_pressed = true;
        }
        a_pressed = true;
    }else{
        //a not pressed
        if(a_pressed == true){
           a_pressed = false;
           a_just_realsed = true;
        }
    }


    if(get_keystate(keycode::s) == true){
        if(s_pressed == false){
           s_pressed = true;
           s_just_pressed = true;
        }
        s_pressed = true;
    }else{
        //w not pressed
        if(s_pressed == true){
           s_pressed = false;
           s_just_realsed = true;
        }
    }

    if(get_keystate(keycode::d) == true){
        if(d_pressed == false){
           d_pressed = true;
           d_just_pressed = true;
        }
        d_pressed = true;
    }else{
        //w not pressed
        if(d_pressed == true){
           d_pressed = false;
           d_just_realsed = true;
        }
    }
}