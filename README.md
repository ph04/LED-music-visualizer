# LED-music-visualizer

The original project was made by Devon Crawford, and every credit goes to him.
Here you can find his GitHub project: https://github.com/DevonCrawford/LED-Music-Visualizer

This project involves a led strip of 60 leds (the length is editable).
There is a music-to-voltage circuit, a circuit to amplify the volume, a circuit to invert the signal and a rotary potentiometer trimpot to adjust the leds' speed.

I'll attach the whole circuit aswell.

In the `src/leds.ino` I didn't use the library that Devon used, instead I used the Adafruit Neopixel library, which is downloadable directly from the Arduino IDE.

In the given file, by default lower sound means white, instead higher sound means red.
