/**
 * Function detects, if provided morse code is valid or no,
 * If code is valid, function returns 1. If not, returns 0.
 * @param morse the word endoced into morse code
 */
int is_morse_code_valid(const char morse[]);

/**
 * Function returns a string encoded into morse code.
 * @param text plain text string
 * @param ouput buffer for encoded string
 */
void text_to_morse(const char text[], char output[]);


/**
 * Function returns a string decoded into readable form (alphabet).
 * @param morse morse code string
 * @param ouput buffer for decoded string
 */
void morse_to_text(const char morse[], char output[]);