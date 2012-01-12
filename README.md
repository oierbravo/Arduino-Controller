Arduino Controller 0.0.1
========================

Basic Arduino Controller.

- By now sends MIDI data over the serial port.
- 20 buttons are wired to a MUX shield.
- In my case I use a MIDI shield so I can connect it to a soundcard but its possible to use a "Serial to MIDI" conversor and use USB connection.

###STEPS

1. Wire all the buttons to the mux shield.
2. Stack both shields (MUX and MIDI) on top of the Arduino board.
3. Upload the sketch(this can also be the first step).
4. Plug the MIDI OUT of the MIDI shield to the MIDI IN of the soundcard.

###RECIPE LIST
- Arduino
- Mux Shield
- 20 arcade buttons
- MIDI Shield (Optional)

###IDEAS and next experiments for next versions
- Use an ethernet shield to send OSC
  - PoE so only one wire is needed.
- Use a wifi shield to send OSC.
- More components
 - Add analog sliders and knobs
 - Rotary encoders
 - HDD rotary
 - LEDs (a lot,XD)
 - Analog Joysticks
 - Pressure sensors
- Recive and process incoming data (MIDI/OSC)