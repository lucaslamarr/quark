// ---------------------------------------------------------------------------------------
// quark_input.h - C99 single file controller input library for Windows game development
// ---------------------------------------------------------------------------------------

/*
------------------------------------------------------------------------------------------
License Information
------------------------------------------------------------------------------------------

MIT License

Copyright (c) 2026 Lucas LaMarr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

------------------------------------------------------------------------------------------
Important Notice
------------------------------------------------------------------------------------------

This library has only been tested for 64-bit Windows 11 and has certain
functionality that depends on native platform code. The entire library is
guarded at the top of quark_input.h to ensure that it is not accidentally 
used for another platform rather than cluttering the file with _WIN32 guards 
and prefixing Windows specific functions with win32.

This library uses XInput and was tested using Xbox One controllers.
Any similar controller should work, however support is not guaranteed.

This library only handles controller input and does not 
cover mouse and keyboard controls because the main windows procedure for
the application has a way to handle that already. It is up to the user to
figure out how to organize keyboard and mouse input however they want or
just the windows messages directly for input listening.

------------------------------------------------------------------------------------------
Using quark_input
------------------------------------------------------------------------------------------

quark_input has been compiled and checked with the following compilers
- MSVC (19.51.36252)
- GCC (16.1.0)

Just drag and drop quark_input.h into your project and start using it.
No extra installation or tooling required!

Because quark_input does not contain a dedicated quark_input.c implementation
file it must have a single translation unit to contain both the declarations
and definitions. This can be done quite easily by just writing the following
inside of your main entry point file.

#define QUARK_INPUT_IMPLEMENTATION
#include "quark_input.h"

This just gives your main translation unit access to the entire quark_input.h
library and knows both the declaration signatures as well as the definitions.
Any other translation units that use the library can simply include the
header file like normal and does not need to have any additional macro added.
*/

#ifdef _WIN32

#ifndef QUARK_INPUT_H
#define QUARK_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------------------
// Dependencies
// ---------------------------------------------------------------------------------------

#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <Xinput.h>

// ---------------------------------------------------------------------------------------
// Structs
// ---------------------------------------------------------------------------------------

typedef struct quark_controller
{
	WORD buttons_current;        // Bitmask that flips bits for the buttons being pressed in the current frame
    WORD buttons_previous;       // Bitmask that flips bits for the buttons being pressed last frame

    BYTE trigger_left_current;   // Analog value between 0-255 for left trigger move strength
    BYTE trigger_right_current;  // Analog value between 0-255 for right trigger move strength

	SHORT thumbstick_left_x;     // The weight being applied horizontally to the left thumbstick
	SHORT thumbstick_left_y;     // The weight being applied vertically to the left thumbstick
    SHORT thumbstick_right_x;    // The weight being applied horizontally to the right thumbstick
    SHORT thumbstick_right_y;    // The weight being applied vertically to the right thumbstick

	int connected;
} quark_controller;

// ---------------------------------------------------------------------------------------
// Forward Declarations
// ---------------------------------------------------------------------------------------

extern void quark_controller_poll(void); // Checks for controller connections and input changes
extern int quark_controller_connected(void);

extern int quark_controller_button_bottom_tapped(void); // Returns 1 if the A button is tapped
extern int quark_controller_button_bottom_held(void);   // Returns 1 if the A button is held
extern int quark_controller_button_top_tapped(void);    // Returns 1 if the Y button is tapped
extern int quark_controller_button_top_held(void);      // Returns 1 if the Y button is held
extern int quark_controller_button_left_tapped(void);   // Returns 1 if the X button is tapped
extern int quark_controller_button_left_held(void);     // Returns 1 if the X button is held
extern int quark_controller_button_right_tapped(void);  // Returns 1 if the B button is tapped
extern int quark_controller_button_right_held(void);    // Returns 1 if the B button is held
extern int quark_controller_button_back_tapped(void);   // Returns 1 if the Select button is tapped
extern int quark_controller_button_back_held(void);     // Returns 1 if the Select button is held
extern int quark_controller_button_start_tapped(void);  // Returns 1 if the Start button is tapped
extern int quark_controller_button_start_held(void);    // Returns 1 if the Start button is held
extern int quark_controller_dpad_bottom_tapped(void);   // Returns 1 if the DPAD Bottom button is tapped
extern int quark_controller_dpad_bottom_held(void);     // Returns 1 if the DPAD Bottom button is held
extern int quark_controller_dpad_top_tapped(void);      // Returns 1 if the DPAD Top button is tapped
extern int quark_controller_dpad_top_held(void);        // Returns 1 if the DPAD Top button is held
extern int quark_controller_dpad_left_tapped(void);     // Returns 1 if the DPAD Left button is tapped
extern int quark_controller_dpad_left_held(void);       // Returns 1 if the DPAD Left button is held
extern int quark_controller_dpad_right_tapped(void);    // Returns 1 if the DPAD Right button is tapped
extern int quark_controller_dpad_right_held(void);      // Returns 1 if the DPAD Right button is held
extern int quark_controller_stick_left_tapped(void);    // Returns 1 if the Stick Left button is tapped
extern int quark_controller_stick_left_held(void);      // Returns 1 if the Stick Left button is held
extern int quark_controller_stick_right_tapped(void);   // Returns 1 if the Stick Right button is tapped
extern int quark_controller_stick_right_held(void);     // Returns 1 if the Stick Right button is held
extern int quark_controller_bumper_left_tapped(void);   // Returns 1 if the Bumper Left button is tapped
extern int quark_controller_bumper_left_held(void);     // Returns 1 if the Bumper Left button is held
extern int quark_controller_bumper_right_tapped(void);  // Returns 1 if the Bumper Right button is tapped
extern int quark_controller_bumper_right_held(void);    // Returns 1 if the Bumper Right button is held
extern int quark_controller_trigger_left_tapped(void);  // Returns 1 if the Trigger Left button is tapped
extern int quark_controller_trigger_left_held(void);    // Returns 1 if the Trigger Left button is held
extern int quark_controller_trigger_right_tapped(void); // Returns 1 if the Trigger Right button is tapped
extern int quark_controller_trigger_right_held(void);   // Returns 1 if the Trigger Right button is held

extern float quark_controller_stick_left_x(void);  // Returns the weight of horizontal input being applied to the Left Thumbstick
extern float quark_controller_stick_left_y(void);  // Returns the weight of vertical input being applied to the Left Thumbstick
extern float quark_controller_stick_right_x(void); // Returns the weight of horizontal input being applied to the Right Thumbstick
extern float quark_controller_stick_right_y(void); // Returns the weight of vertical input being applied to the Right Thumbstick

extern void quark_controller_vibrate_set(uint16_t vibrationLeft, uint16_t vibrationRight); // Sets vibration for a controller
extern void quark_controller_vibrate_stop(void); // Stops all vibration for a controller
#ifdef __cplusplus
}
#endif // extern "C"
#endif // QUARK_INPUT_H


#ifdef QUARK_INPUT_IMPLEMENTATION
#ifndef QUARK_INPUT_IMPLEMENTATION_INCLUDED
#define QUARK_INPUT_IMPLEMENTATION_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------------------
// Internal Globals
// ---------------------------------------------------------------------------------------

// Internal controller, keyboard and mouse for a single player
static quark_controller quark_internal_controller_one = { 0 };

// ---------------------------------------------------------------------------------------
// Internal Constants
// ---------------------------------------------------------------------------------------

#define QUARK_INTERNAL_STICK_MAX 32767.0f
#define QUARK_INTERNAL_STICK_MIN 32768.0f   

// ---------------------------------------------------------------------------------------
// Definitions
// ---------------------------------------------------------------------------------------

void quark_controller_poll(void)
{
    XINPUT_STATE state = { 0 };

    // Takes whatever was last stored inside of buttons_current from the previous frame
    WORD previousButtonsState = quark_internal_controller_one.buttons_current;

    if (XInputGetState(0, &state) == ERROR_SUCCESS)
    {
        quark_internal_controller_one.connected = 1;

        quark_internal_controller_one.buttons_current  = state.Gamepad.wButtons;
        quark_internal_controller_one.buttons_previous = quark_internal_controller_one.buttons_current & ~previousButtonsState;

        quark_internal_controller_one.trigger_left_current  = state.Gamepad.bLeftTrigger;
        quark_internal_controller_one.trigger_right_current = state.Gamepad.bRightTrigger;

        quark_internal_controller_one.thumbstick_left_x  = state.Gamepad.sThumbLX;
        quark_internal_controller_one.thumbstick_left_y  = state.Gamepad.sThumbLY;
        quark_internal_controller_one.thumbstick_right_x = state.Gamepad.sThumbRX;
        quark_internal_controller_one.thumbstick_right_y = state.Gamepad.sThumbRY;
    }
    else
    {
        quark_internal_controller_one.connected = 0;

        quark_internal_controller_one.buttons_current  = 0;
        quark_internal_controller_one.buttons_previous = 0;
                      
        quark_internal_controller_one.trigger_left_current  = 0;
        quark_internal_controller_one.trigger_right_current = 0;
                      
        quark_internal_controller_one.thumbstick_left_x  = 0;
        quark_internal_controller_one.thumbstick_left_y  = 0;
        quark_internal_controller_one.thumbstick_right_x = 0;
        quark_internal_controller_one.thumbstick_right_y = 0;
    }
}

int quark_controller_connected(void)
{
    return quark_internal_controller_one.connected;
}

int quark_controller_button_bottom_tapped(void) { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_A)              ? 1 : 0; }
int quark_controller_button_bottom_held(void)   { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_A)              ? 1 : 0; }
int quark_controller_button_top_tapped(void)    { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_Y)              ? 1 : 0; }
int quark_controller_button_top_held(void)      { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_Y)              ? 1 : 0; }
int quark_controller_button_left_tapped(void)   { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_X)              ? 1 : 0; }
int quark_controller_button_left_held(void)     { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_X)              ? 1 : 0; }
int quark_controller_button_right_tapped(void)  { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_B)              ? 1 : 0; }
int quark_controller_button_right_held(void)    { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_B)              ? 1 : 0; }
int quark_controller_button_back_tapped(void)   { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_BACK)           ? 1 : 0; }
int quark_controller_button_back_held(void)     { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_BACK)           ? 1 : 0; }
int quark_controller_button_start_tapped(void)  { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_START)          ? 1 : 0; }
int quark_controller_button_start_held(void)    { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_START)          ? 1 : 0; }
int quark_controller_dpad_bottom_tapped(void)   { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_DPAD_DOWN)      ? 1 : 0; }
int quark_controller_dpad_bottom_held(void)     { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_DPAD_DOWN)      ? 1 : 0; }
int quark_controller_dpad_top_tapped(void)      { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_DPAD_UP)        ? 1 : 0; }
int quark_controller_dpad_top_held(void)        { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_DPAD_UP)        ? 1 : 0; }
int quark_controller_dpad_left_tapped(void)     { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_DPAD_LEFT)      ? 1 : 0; }
int quark_controller_dpad_left_held(void)       { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_DPAD_LEFT)      ? 1 : 0; }
int quark_controller_dpad_right_tapped(void)    { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_DPAD_RIGHT)     ? 1 : 0; }
int quark_controller_dpad_right_held(void)      { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_DPAD_RIGHT)     ? 1 : 0; }
int quark_controller_stick_left_tapped(void)    { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_LEFT_THUMB)     ? 1 : 0; }
int quark_controller_stick_left_held(void)      { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_LEFT_THUMB)     ? 1 : 0; }
int quark_controller_stick_right_tapped(void)   { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_RIGHT_THUMB)    ? 1 : 0; }
int quark_controller_stick_right_held(void)     { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_RIGHT_THUMB)    ? 1 : 0; }
int quark_controller_bumper_left_tapped(void)   { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_LEFT_SHOULDER)  ? 1 : 0; }
int quark_controller_bumper_left_held(void)     { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_LEFT_SHOULDER)  ? 1 : 0; }
int quark_controller_bumper_right_tapped(void)  { return (quark_internal_controller_one.buttons_previous & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 1 : 0; }
int quark_controller_bumper_right_held(void)    { return (quark_internal_controller_one.buttons_current  & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 1 : 0; }
                                                                    
int quark_controller_trigger_left_held(void)    { return (quark_internal_controller_one.trigger_left_current  > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? 1 : 0; }                                                                  
int quark_controller_trigger_right_held(void)   { return (quark_internal_controller_one.trigger_right_current > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? 1 : 0; }

float quark_controller_stick_left_x(void)
{
    float value = (float)quark_internal_controller_one.thumbstick_left_x;

    if (value <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
    {
        return 0.0f;
    }

    return value < 0.0f ? value / QUARK_INTERNAL_STICK_MIN : value / QUARK_INTERNAL_STICK_MAX;
}

float quark_controller_stick_left_y(void)
{
    float value = (float)quark_internal_controller_one.thumbstick_left_y;

    if (value <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
    {
        return 0.0f;
    }

    return value < 0.0f ? value / QUARK_INTERNAL_STICK_MIN : value / QUARK_INTERNAL_STICK_MAX;
}

float quark_controller_stick_right_x(void)
{
    float value = (float)quark_internal_controller_one.thumbstick_right_x;

    if (value <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && value >= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
    {
        return 0.0f;
    }

    return value < 0.0f ? value / QUARK_INTERNAL_STICK_MIN : value / QUARK_INTERNAL_STICK_MAX;
}

float quark_controller_stick_right_y(void)
{
    float value = (float)quark_internal_controller_one.thumbstick_right_y;

    if (value <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && value >= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
    {
        return 0.0f;
    }

    return value < 0.0f ? value / QUARK_INTERNAL_STICK_MIN : value / QUARK_INTERNAL_STICK_MAX;
}

extern void quark_controller_vibrate_set(uint16_t vibrationLeft, uint16_t vibrationRight)
{
    XINPUT_VIBRATION vibration = {0};
    vibration.wLeftMotorSpeed  = vibrationLeft;
    vibration.wRightMotorSpeed = vibrationRight;

    XInputSetState(0, &vibration);
}

extern void quark_controller_vibrate_stop(void)
{
    XINPUT_VIBRATION vibration = { 0 };
    vibration.wLeftMotorSpeed  = 0;
    vibration.wRightMotorSpeed = 0;

    XInputSetState(0, &vibration);
}
#ifdef __cplusplus
}
#endif // extern "C"
#endif // QUARK_INPUT_IMPLEMENTATION_INCLUDED 
#endif // QUARK_INPUT_IMPLEMENTATION 

#endif