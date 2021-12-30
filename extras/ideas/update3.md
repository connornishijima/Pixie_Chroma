# WELCOME BACK!

This week, we're going to go over two topics, ***how to get started with your first Pixies*** and ***how "Shortcodes" are parsed!*** 

## PIXIES ON DAY 1

TBD

----------------------------------------------------------------------------------
## HOW SHORTCODES ARE PARSED



### WHAT ARE SHORTCODES USED FOR?

"Shortcodes" are small snippets of text that allow you to sneak picture data into strings of text you're sending to your Pixie Chromas!

### A BIT OF HISTORY

The classic Pixie and its Arduino library used a similar system. These were hard-coded arrays that had 5 bytes in them, whose binary represented the 5 columns of image data that should be shown. For example, a line from `Pixie_Icon_Pack.h` in the original library:

```c++
uint8_t PIX_HEART[5] = {0x0C,0x12,0x24,0x12,0x0C};
```

This 5x7 Icon of a `HEART` could be used like so:
```c++
pix.clear();
pix.print( "WE " );
pix.print( PIX_HEART );
pix.print( " YOU!" );
pix.show();

// You could also use pix.print( 0x0C,0x12,0x24,0x12,0x0C ); to input custom bitmap data (5 columns with 7 bits of data)
```

You may have noticed that there is no way to include ASCII text *and* the Icon in the same function call. This is okay for static text, but it made it impossible to use things like `pix.scroll();` with both data types at the same time.

### ENTER "SHORTCODES"

Shortcodes are my solution to this issue. By using special sequences of characters, the Pixie Chroma library can detect when an Icon is needed within a normal ASCII string. For example:

```c++
pix.clear();
pix.print( "WE [:HEART:] YOU!" );
pix.show();
```

Notice the strange `[:` and `:]` in there? Those are indicators of when a "Shortcode" begins and ends. The name "HEART" is picked out by a preprocessor as the string is being rendered to the displays!

### WHAT THE...?

How is a string "evaluated" to return the data from `uint8_t PIX_HEART[5] = {0x0C,0x12,0x24,0x12,0x0C};`? C++ can't eval() strings for variable names! This is true. Instead, the file storing the Icons has been reformatted:

#### OLD:
```c++
...
uint8_t PIX_CIRCLE[]           = {0x1C,0x22,0x22,0x22,0x1C};
uint8_t PIX_RECTANGLE[]        = {0x7F,0x41,0x41,0x41,0x7F};
uint8_t PIX_EXPORT[]           = {0x74,0x42,0x5F,0x42,0x74};
uint8_t PIX_SAVE[]             = {0x3E,0x22,0x2E,0x26,0x3C};
uint8_t PIX_CLOCK[]            = {0x1C,0x22,0x2E,0x32,0x1C};
uint8_t PIX_STOPWATCH[]        = {0x38,0x4D,0x77,0x45,0x38};
uint8_t PIX_TV[]               = {0x7D,0x46,0x44,0x46,0x7D};
uint8_t PIX_COPY[]             = {0x0F,0x39,0x29,0x2F,0x3C};
...
```
#### NEW:
```c++
static const uint8_t PIXIE_SHORTCODE_LIBRARY[] = {
  // SHORTCODE                COLUMN DATA               MARK  NAME                    TERMINATOR                         
  ...
  /* [:CIRCLE:]            */ 0x1C,0x22,0x22,0x22,0x1C, 213, 'C','I','R','C','L','E', 0,
  /* [:RECTANGLE:]         */ 0x7F,0x41,0x41,0x41,0x7F, 216, 'R','E','C','T','A','N','G','L','E', 0,
  /* [:EXPORT:]            */ 0x74,0x42,0x5F,0x42,0x74, 213, 'E','X','P','O','R','T', 0,
  /* [:SAVE:]              */ 0x3E,0x22,0x2E,0x26,0x3C, 211, 'S','A','V','E', 0,
  /* [:CLOCK:]             */ 0x1C,0x22,0x2E,0x32,0x1C, 212, 'C','L','O','C','K', 0,
  /* [:STOPWATCH:]         */ 0x38,0x4D,0x77,0x45,0x38, 216, 'S','T','O','P','W','A','T','C','H', 0,
  /* [:TV:]                */ 0x7D,0x46,0x44,0x46,0x7D, 209, 'T','V', 0,
  /* [:COPY:]              */ 0x0F,0x39,0x29,0x2F,0x3C, 211, 'C','O','P','Y', 0,
  ...
};
```
What's going on here? Let's take a step-by-step look into how Icons are found inside this massive 1-dimensional array!

### INITIAL PARSING

As an example, let's see how a Shortcode is parsed.
```c++
pix.print( "Mode: [:CLOCK:]" );
```
The first 6 characters are normal text, and are rendered as usual. `"Mode: "`

At the 7th character though, the parser sees a `[`. It skips ahead one character to see if it is followed by a colon `:`. Since the parser finds a colon, it knows that the data that follows is a Shortcode and begins collecting the Icon name! (The parser is not currently rendering what it sees, it stopped at `"Mode: "`.)

(This combination of `[:` was chosen due to it's low likelihood of occurring "naturally".)

At 14th character, the parser sees a colon `:` and peeks ahead one character to verify that it is followed by a closing bracket `]`. Once the end of the Shortcode is found, the characters of the Icon name collected so far (`CLOCK`) are sent to a lookup function.

### LOOKUP TABLE

Alright, back to that weird 1-D array with all of the bitmap data and names. It has 4 types of data:

- **COLUMN DATA** (The bitmap bytes)
- **MARK BYTE** (Used for faster lookups)
- **NAME DATA** (ASCII name of Icon)
- **TERMINATOR** (Used to denote end of NAME DATA strings

This crazy array is used to find the corresponding bitmap data for an Icon name like `CLOCK`. With 240 preset Icons in here, lookups need to be fast. (There's currently 3,480 bytes in this lookup table.) What's the fastest way to find a match in here?

### SMARTER SEARCHING

Since iterating over every single byte in this array could take a long time ( **long** being slower than **freakin' instantly**), we need a cheat. While it's easy enough to skim the above array with your eyes to find a match, your microcontroller doesn't get the luxury of formatting and sees the data like this:
```c++
...
0x1C, 0x22, 0x22, 0x22, 0x1C,  213,  'C',  'I',  'R',  'C',  'L',  'E',    0, 0x7F, 0x41, 0x41, 0x41,
0x7F,  216,  'R',  'E',  'C',  'T',  'A',  'N',  'G',  'L',  'E',    0, 0x74, 0x42, 0x5F, 0x42, 0x74,
 213,  'E',  'X',  'P',  'O',  'R',  'T',    0, 0x3E, 0x22, 0x2E, 0x26, 0x3C,  211,  'S',  'A',  'V',
 'E',    0, 0x1C, 0x22, 0x2E, 0x32, 0x1C,  212,  'C',  'L',  'O',  'C',  'K',    0, 0x38, 0x4D, 0x77,
0x45, 0x38,  216,  'S',  'T',  'O',  'P',  'W',  'A',  'T',  'C',  'H',    0, 0x7D, 0x46, 0x44, 0x46,
...
```
How long does it take you to find "CLOCK" in there? How could you find a matching Icon in an (average of) 130 microseconds? (That's 7,692 times a second!) Our cheat here is "MARK" bytes.

### MARK BYTES TO THE RESCUE!

One of the strangest looking things about this 1-D array is that it looks as if it's mixing data types. There's decimal numbers for mark bytes and terminators, HEX for bitmap data, and even text for names. However, all of these are just stored as `uint8_t` bytes, which are numbers ranging from 0 to 255. In fact, *this* is actually closer to how your microcontroller sees this array:
```c++
...
28,  34,  34,  34,  28,  213, 67,  73,  82,  67,  76,  69, 0,   127, 65,  65, 65, 
127, 216, 82,  69,  67,  84,  65,  78,  71,  76,  69,  0,  116, 66,  95,  66, 116, 
213, 69,  88,  80,  79,  82,  84,  0,   62,  34,  46,  38, 60,  211, 83,  65, 86, 
69,  0,   28,  34,  46,  50,  28,  212, 67,  76,  79,  67, 75,  0,   56,  77, 119, 
69,  56,  216, 83,  84,  79,  80,  87,  65,  84,  67,  72, 0,   125, 70,  68, 70, 
...
```
However, some of these bytes are special. Bitmap column data is never greater than 127, and neither is ASCII text or terminators. The only bytes in this array that are greater than 127 are the MARK bytes. These are used as a shortcut for quicker lookups like so:

1. Scan array until a MARK byte is found (> 127)
2. This MARK byte is 200, plus the number of steps in the array until the next one. (i.e. `213` for 13 steps)
3. Once a MARK is found, the very next item is the first character of that Icon's name.
4. If the character we're reading matches the first character of the name we're looking for, continue reading
5. If it isn't, we know that we have moved 1 step since the MARK, so let's jump straight to the next MARK (`index += (213 - 200) - 1`)
6. Repeat from step 2.
7. Once a full match of the name is found, (we hit a terminator) we know that the 5 bytes preceding the last MARK are the bitmap column data we need to return!
8. If we found a full match so far but didn't find a terminator afterwards, maybe this is a different Icon with a similar name ("CLOCK" vs "CLOCKWISE")

With this system, we can return an Icon at the start of the array in just 96 microseconds, and the last Icon in just 192 microseconds!

### Why not JSON?

While ArduinoJSON could likely work, this has the smallest memory and computation footprint I could come up with.

### RETURNING FOUND MATCHES

Since we now have the bitmap data that matches `[:CLOCK:]`, we can print it to the display buffer and return to rendering the original 'pix.print()' call until the string is done or another Shortcode is found!

### WHAT ABOUT CUSTOM ICONS?

Similar to the
```c++
pix.print( 0x0C,0x12,0x24,0x12,0x0C );
```
function on the original Pixies to show custom Icons, Shortcodes can be formatted to show custom Icons as well!
```c++
pix.print( "WE [:#0C1224120C:] YOU!" ); // Custom
```
This is very similar to preset Shortcodes with names, but has a `#` to denote that the following 10 chars are 5 bytes of custom HEX data!

### NEW THINGS POSSIBLE WITH SHORTCODES

All of this *just* to sneak Icons into text? Yes! Since Icons are now represented just by text via Shortcodes, any thing that uses ASCII can use Icons! You can send Icon data over serial, WiFi, or pass Icons to any function that takes text, such as scrolling functions! It's also much nicer to write:

	pix.print( "WE [:HEART:] YOU!" );

...instead of:

    pix.print( "WE " );
    pix.print( PIX_HEART );
    pix.print( " YOU!" );

### I DON'T KNOW WHAT ANY OF THAT MEANT

No worries! All you need to know is how Shortcodes (like `[:SNOW:]`) are used:

```c++
pix.print( "Here's a smile: [:SMILE:]" ); // Built-in preset Icon
```

```c++
pix.print( "Here's a zig-zag: [:#00442A1100:]" ); // Custom "zig-zag" icon defined with hex data generated by the Shortcode Library tool.
```

To see all presets and make your own custom icons with no technical knowledge needed, try our [Shortcode Library](https://connornishijima.github.io/Pixie_Chroma/?section=shortcodes)! There's over 200 presets to choose from or you can draw your own!
