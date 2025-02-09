export module Kiss.SBI:sbi;

import Kiss.Base;

namespace Kiss::SBI {

struct Ret {
    long error;
    long value;
};

export Ret call(long arg0, long arg1, long arg2, long arg3, long arg4, long arg5, long fid, long eid) {
    register long a0 __asm__("a0") = arg0;
    register long a1 __asm__("a1") = arg1;
    register long a2 __asm__("a2") = arg2;
    register long a3 __asm__("a3") = arg3;
    register long a4 __asm__("a4") = arg4;
    register long a5 __asm__("a5") = arg5;
    register long a6 __asm__("a6") = fid;
    register long a7 __asm__("a7") = eid;

    __asm__ __volatile__("ecall"
                         : "=r"(a0), "=r"(a1)
                         : "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5),
                           "r"(a6), "r"(a7)
                         : "memory");
    return (Ret){.error = a0, .value = a1};
}

export Ret consolePutchar(int ch) {
    return call(ch, 0, 0, 0, 0, 0, 0, 1);
}

export void consolePuts(String str) {
    for (char const c : str) {
        consolePutchar(c);
    }
}

export void consolePuti(long i, usize base) {
    Array<char, sizeof(i) * __CHAR_BIT__> buf;
    if (i < 0) {
        consolePutchar('-');
        i = -i;
    }

    char* p = buf.begin();
    while (i > 0) {
        usize digit = i % base;
        i /= base;
        if (digit < 10)
            *p++ = digit + '0';
        else
            *p++ = digit + 'a' - 10;
    }

    for (; p >= buf.begin(); --p) {
        consolePutchar(*p);
    }
}

} // namespace Kiss::SBI
