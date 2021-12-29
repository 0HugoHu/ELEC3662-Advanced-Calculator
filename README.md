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
|`Display Graphics`|📛 Yes 💡 |This feature is easy to implement, but I don't want too many animation effects to interfere with the user's use. But the prompting statements are all there, and I add a simple progress bar animation in the welcome page|
|`LED Indicators`|✅ Yes 💡|Four LEDs to show animation for succeess\failure and shift status|
|`Correct Result`|✅ Yes|Show integer and floating values in correct form, e.g. "2.5\*2=5", "5/2=2.5". Removed unnecessary zeros, e.g. normally "2.6/2=1.3000", here I show the result as "2.6/2=1.3" |
|`40 Characters Expression`|✅ Yes 💡|Up to 40 characters length expression can be calculated|
|`Adjust Screen Contrast`|⭕ No 💡|Couln't achieve this function due to the lack of a sliding resistor. PWM modulation is an alternative way, but I leave it here|

# Circuit Scheme
![`MFS9DY8L(H(QJO6 )TW75I](https://user-images.githubusercontent.com/46556200/147673201-6df4e6f1-79c0-4577-bced-fd01f6145498.png)

\*4-bit mode is applied in this project.

# Highligts
✔ **Technically Impressive Features**

The most technically challenging part of this project is to put the operands and operators on the stack separately, and then compute them according to the operators' priority. So my advanced calculator does much more than just add, subtract, multiply, and divide two operands. It can also embed arbitrary layers of brackets and perform multiplication and logarithmic calculations within the 40-character length limit (limited by the maximum 48 characters on a line of the LCD screen).

Example:


The priority table (the larger the higher):

|Operator/Operands            | Priority       |
|-------------------------|-------------------------------|
|UNKOWN|0|
|+, -|1|
|*, /|2|
|e, log|3|
|. (Point)|4|
|PI, ANS|5|


✔ **Innovative Features**

1. Machine-to-Human Expression Translation

The question asks for "x" instead of "\*" for the multiplication sign and "1.2E3" for 1.2\*10^3, but I went a step further and did the following conversion (X and Y denote two operands):

|Enter            | Result       | Notes  |
|-------------------------|-------------------------------|-------------------------------|
|\*|x|Multiplication|
|a|ANS|Last Answer|
|p|PI|π Constant|
|XeY|X^Y|Exponential|
|XlY|logX(Y)|Logarithm|

Example:


2. Four LEDs Indicator

I have used four LEDs from left to right: white, orange, blue, and pink to indicate the status of the calculator, so that the user can clearly know the results of each step. In the table below, ⚫ indicates that the light in that position is not on, and the circle with colors (⚪🟡🔵🔴) indicates that it is on. 🔘 indicates any condition.

|LEDs Status          |Explaination       |
|-------------------------|-------------------------------|
|⚫⚫⚫⚫|The power if off|
|⚫⚫⚫⚫->⚫⚫⚫🔴->⚪⚫⚫⚫|Power on, initialization succeeds|
|🔘🔘🔘🔘->⚫⚫⚫🔴->🔘🔘🔘🔘|Error occurs|
|⚪⚫⚫⚫|No shift|
|⚪🟡⚫⚫|Shift A|
|⚪🟡🔵⚫|Double-Shift A|
|⚪🟡🔵🔴|Lock state|
|⚪🟡🔵🔴->⚫⚫⚫⚫->...3 times...->⚫⚫⚫⚫|Operation succeeds|
|⚪🟡⚫⚫->⚫🟡🔵⚫->⚫⚫🔵🔴->⚪⚫⚫🔴->...3 times...->⚪⚫⚫🔴|Password correct, log in|

Example:


# Live Demo

# Contribution
The project's LCD driver function and EEPROM initialization, reading and saving methods are referenced from https://github.com/el15cr/ELEC3662-Calculator/blob/master.

The project source code will be released later. Feel free to raise any question in the issue part.


