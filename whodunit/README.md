# Questions

## What's `stdint.h`?

stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to
allow programmers to write more portable code by providing a set of typedefs that specify
exact-width integer types, together with the defined minimum and maximum allowable values for
each type, using macros

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

 It makes clear that you intend to use the data a specific way. uint24_t means an integer that is exactly
 24 bits wide.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1 byte is a 'BYTE'
4 bytes is a 'DWORD'
4 bytes is a 'LONG'
2 bytes is a 'WORD'

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x4d42

## What's the difference between `bfSize` and `biSize`?

bfSize is the total size of the file in bytes, including pixels, paddings and headers,
bfSize = biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
biSize is the size of the BITMAPINFOHEADER only. It is 40 bytes.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB with the origin at the upper left corne

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The biBitCount member of the BITMAPINFOHEADER structure determines the number of
bits that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

File does not exist or insufficient permissions.

## Why is the third argument to `fread` always `1` in our code?

We read one pixel(one size of RGBTRIPLE) each time.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4
        = (4 - (3 * 3) % 4) % 4
        = (4 - 1) % 4
        = 3

## What does `fseek` do?

function int fseek(FILE *stream, long int offset, int whence) sets the file position
of the stream to the given offset

## What is `SEEK_CUR`?

Current position of the file pointer

## Whodunit?

Get the information hiden in the image.
