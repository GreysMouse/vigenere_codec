About:

A program for encrypting Latin-script text using the Vigenère cipher.

Usage:

    <program name> <key> <input file> [<output file>]

where \<key\> is the cipher's code word, which must consist only of the letters a-z.

If \<output file\> not specified, the result will be written to the standard output stream.

The \<input file\> must contain valid text in Latin characters.

Program can be compiled with macro symbols:

- DECODE_MODE - compile program as decoder;

- SKIP_NON_LETTERS - remove all characters (including whitespace) except a–z from the output text;

- KEEP_LOWERCASE - get the output text in lowercase;

- KEEP_UPPERCASE - get the output text in uppercase.
