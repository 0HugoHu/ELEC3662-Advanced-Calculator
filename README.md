# ELEC3662-Advanced-Calculator
ELEC3662 / XJEL3662 Embedded Systems Mini Project. 

Based on Tiva C Series TM4C123G LaunchPad, HITACHI HD44780U 16 * 2 LCD Screen, and a 4 \* 4 matrix Keypad.

# Live Demo

A Video and some photos are waiting to upload...

![Examples](https://user-images.githubusercontent.com/46556200/147748677-6a31a717-aea8-428d-a483-b6486f78a45d.png)


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
|`Dangerous Calculation Avoided`|✅ Yes 💡|When calculate "1/0" or "log2(-41)", result shows "0" instead of the program crashing|、
|`Key De-jittering`|✅ Yes 💡|Avoid unintentional inputs due to false touches and environmental noise by detecting the rising edge and setting a short time to repeat the detection twice|

# Circuit Scheme

![`MFS9DY8L(H(QJO6 )TW75I](https://user-images.githubusercontent.com/46556200/147673201-6df4e6f1-79c0-4577-bced-fd01f6145498.png)

\*4-bit mode is applied in this project.

# Highligts
✔ **Technically Impressive Features**

The most technically challenging part of this project is to put the operands and operators on the stack separately, and then compute them according to the operators' priority. So my advanced calculator does much more than just add, subtract, multiply, and divide two operands. It can also embed arbitrary layers of brackets and perform multiplication and logarithmic calculations within the 40-character length limit (limited by the maximum 48 characters on a line of the LCD screen).

Example:

Three-layer brackets:

![IMG_20211229_233610_edit_1269905246855174](https://user-images.githubusercontent.com/46556200/147678899-a8db4b86-e0d1-410a-a96f-83b06fc6c70e.jpg)

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

**⑴ Machine-to-Human Expression Translation**

The question asks for "x" instead of "\*" for the multiplication sign and "1.2E3" for 1.2\*10^3, but I went a step further and did the following conversion (X and Y denote two operands):

|Enter            | Result       | Notes  |
|-------------------------|-------------------------------|-------------------------------|
|\*|x|Multiplication|
|a|ANS|Last Answer|
|p|PI|π Constant|
|XeY|X^Y|Exponential|
|XlY|logX(Y)|Logarithm|

Example:

Originally entered expression:

![IMG_20211229_233820_edit_1270033546979113](https://user-images.githubusercontent.com/46556200/147679188-d3f8d3ff-d2bf-4529-8297-a3ea719b9f9b.jpg)

Result machine-style expression:

![IMG_20211229_233845_edit_1270053434595256](https://user-images.githubusercontent.com/46556200/147679269-f743fb8e-7f14-40b1-bab5-558ea2a80de1.jpg)


**⑵ Four LEDs Indicator**

I have used four LEDs from left to right: white, orange, blue, and pink to indicate the status of the calculator, so that the user can clearly know the results of each step. In the table below, ⚫ indicates that the light in that position is not on, and the circle with colors (⚪🟡🔵🔴) indicates that it is on. 🔘 indicates any condition.

|LEDs Status          |Explaination       |
|-------------------------|-------------------------------|
|⚫⚫⚫⚫|Power off|
|⚫⚫⚫⚫->⚫⚫⚫🔴->⚪⚫⚫⚫|Power on, initialization succeeds|
|🔘🔘🔘🔘->⚫⚫⚫🔴->🔘🔘🔘🔘|Error occurs|
|⚪⚫⚫⚫|No shift|
|⚪🟡⚫⚫|Shift A|
|⚪🟡🔵⚫|Double-Shift A|
|⚪🟡🔵🔴|Lock state|
|⚪🟡🔵🔴->⚫⚫⚫⚫->...3 times...->⚫⚫⚫⚫|Operation succeeds|
|⚪🟡⚫⚫->⚫🟡🔵⚫->⚫⚫🔵🔴->⚪⚫⚫🔴->...3 times...->⚪⚫⚫🔴|Password correct, log in|

Example:

"LOCK" state with four LEDs all on:

![IMG_20211229_234440](https://user-images.githubusercontent.com/46556200/147679630-8c7638d2-ef20-4e1a-9630-69ccaad89957.jpg)

**⑶ Key De-jittering**

Even if the key status is detected using the correct method, the tiny currents generated by environmental disturbances can easily lead to false touches due to the insecurity at the key interface, requiring the use of keyboard de-jittering to ensure stable input.

Firstly, set positive-edge detection:

> GPIO_PORTE_IS_R &= ~0x0F;     		// Edge-sensitive  
>	GPIO_PORTE_IBE_R &= ~0x0F;    		// Not both edges  
>	GPIO_PORTE_IEV_R |= 0x0F;    			// Rising edge event

Secondly, create a variable to save the last-pressed key, and compare it with the current pressed key.

> // At least trigered twice can be regarded as button pressed  
>	if (_keyValue != lastPressed) {  
>	&nbsp;&nbsp;&nbsp;&nbsp;lastPressed = _keyValue;  
>	&nbsp;&nbsp;&nbsp;&nbsp;SysTickWait(10 * 1000);  
>	&nbsp;&nbsp;&nbsp;&nbsp;return 0x00;  
>	}

Since once we intentionally pressed a key, its voltage change lasts for at least 100ms, far greater than 10 * 1000 = 10ms --enough to be detected twice in sequence. It prevents occationally disturbance-caused voltage changes.


# Statistics

|Files |Lines of Code                     |Explanations|
|----------------|-------------------------------|-----------------------------|
|main.c|370|Entrance. Finate-state Machine|
|TExaS.h|46|Debugger|
|INDICATOR.h|30|LEDs status indicator|
|INDICATOR.c|98| |
|PLL.h|20|Configure system time function|
|PLL.c|66| |
|PORT.h|94|All ports declarations|
|BUFFER.h|30|Store and display inputs|
|BUFFER.c|78| |
|KEY.h|40|Read keypad inputs|
|KEY.c|235| |
|LCD.h|36|Display characters and strings|
|LCD.c|173| |
|CALCULATOR.h|95|Core mathematical algorithms|
|CALCULATOR.c|589| |
|PASSWORD.h|23|Save and read EEPROM|
|PASSWORD.c|48| |
|**Total**|**2071**| |

# Known Bugs
1. When calculate "3++3", the result is 8 --absolutely wrong. Try using "3+(+3)" instead.
2. Under certain conditions, the result still shows unnecessary zeros.
3. The result is incomplete when entering a long expression.

# Contribution
The project's LCD driver function and EEPROM initialization, reading and saving methods are referenced from https://github.com/el15cr/ELEC3662-Calculator/blob/master.

The project source code will be released later. Feel free to raise any question in the issue part.


