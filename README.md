# Simple numitron iv-9 desk clock using 4 shift registers, Arduino Uno(or equivalent) and ds3231 RTC clock

According to documentation, the first iv-9 leg is common, second is indication dot. You need to connect common(first) to GND then every single leg to outputs of your shift register(one by one).

Use this tutorial for connecting shift registers to Arduino: https://www.arduino.cc/en/tutorial/ShiftOut and remember to use caps for the nice flicker-less experience.

Use 0.1pf caps between VCC and GND as a decoupling cap for shift register - VERY IMPORTANT for debugging, strange things may happen if you ignore this step.

Also, use something more capable than 595 shift registers - they might work but also might fail horribly killing your numitron or Arduino or PC.

You can use ds1307 or ds3231 - ds1307 lack temperature monitoring

# Behaviour

After powering on (and setting correct time/date on your RTC) time/date will be pulled from rtc using DS1307RTC library, then after parsing it should be displayed on numitrons (using byte array) for 60 sec. After that - day and month will be displayed(also from rtc) for 1.5 sec and then the year(from rtc) and temperature(if ds3231 is used). The cycle will end and time will be displayed again. Everything is nicely done using fade-in fade-out. It is a very simple concept on which my next project will be based.

# A good read before recreating this project:

Arduino with shift registers:  https://www.arduino.cc/en/tutorial/ShiftOut

Decoupling caps: http://www.thebox.myzen.co.uk/Tutorial/De-coupling.html

Numitron tutorial with informative comments on HackaDay: https://hackaday.com/2011/12/21/numitron-tube-tutorial/

Very helpful documentation on iv-9, can't express my gratefulness - I would be helpless without this good man site: http://www.tube-tester.com/sites/nixie/data/IV-9/iv-9.htm

In-depth about ds3231 RTC clock: https://lastminuteengineers.com/ds3231-rtc-arduino-tutorial/

Dropping Resistor calculator: http://www.gtsparkplugs.com/Dropping_Resistor_Calc.html

-------------------------------------------------------------------------------------------------------------------------------

My Facebook site: https://www.facebook.com/PutridDump

GOOD LUCK
