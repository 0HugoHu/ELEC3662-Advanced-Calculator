# ELEC3662-Advanced-Calculator
ELEC3662 / XJEL3662 Embedded Systems Mini Project. 

Based on Tiva C Series TM4C123G LaunchPad, HITACHI HD44780U 16 * 2 LCD Screen, and a 4 \* 4 matrix Keypad.

# Checklist

💡means extra task.

|Operators            |Completion                     |Notes                        |
|----------------|-------------------------------|-----------------------------|
|`Addition +`|✅ Yes|          |
|`Subtraction -`|✅ Yes| |
|`Multiplication *`|✅ Yes| |
|`Division /`|✅ Yes|  |
|`Exponential e`|✅ Yes 💡|Enter in "2e3", Result shows in "2^3"|
|`Logarithm log`|✅ Yes 💡|Enter in "3l9", Result shows in "log3(9)"|
|`Brackets ()`|✅ Yes 💡|Can be used as "2x(3/(1+1+(1)))"|
|`Decimal .`|✅ Yes|
|`Last-Anwser ANS`|✅ Yes 💡|Enter in "a", Result shows in "ANS"|
|`Pi π`|✅ Yes 💡|Enter in "p", Result shows in "PI"|


|Functions            | Completion        | Notes          |
|-------------------------|-------------------------------|-----------------------------|
|`Shift Function`|✅ Yes|Single-Shift and Double-Shift|
|`Robout Last Character`|✅ Yes|  |
|`Delete Entire Entry`|✅ Yes|  |
|`Human-to-Machine Expression Conversion`|✅ Yes|Convert e.g. "2\*3l9" into "2xlog3(9)"|
|`Password Protection`|✅ Yes 💡|  |
|`Store Password`|✅ Yes 💡|EEPROM is used|
|`Display Graphics`|📛 Yes & No 💡 |This feature is easy to implement, but I don't want too many animation effects to interfere with the user's use. But the prompting statements are all there, and I add a simple point animation in the welcome page|
|`LED Indicators`|✅ Yes 💡|Four LEDs to show animation for succeess\failure and shift status|
|`Correct Result`|✅ Yes|Show integer and floating values in correct form, e.g. "2.5\*2=5", "5/2=2.5" |
|`40 Characters Expression`|✅ Yes 💡|Up to 40 characters length expression can be calculated|
|`Adjust Screen Contrast`|⭕ No 💡|Couln't achieve this function due to the lack of a sliding resistor. PWM modulation is an alternative way, but I leave it here|

# Circuit Scheme


# Highligts

# Live Demo

