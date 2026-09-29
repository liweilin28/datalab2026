/* 警告：不要在这里包含任何其他库，

- 否则运行 test.py 时会报错。
- 即使不包含 <stdio.h>，仍然可以使用 printf 进行调试，
- 不过编译器可能会给出警告。通常来说，不应该忽略编译器警告，
- 但在这里这样做没有问题。
-
- 使用 printf 会干扰脚本捕获程序的运行结果。
- 此时只能使用 ./btest 测试程序的正确性。
- 使用 ./btest 确认所有内容都正确后，删除 printf，
- 再使用 test.py 运行完整测试。
*/


/*
- bitAnd - 只使用 ~ 和 | 实现 x & y
- 示例：bitAnd(4, 5) = 4
- 允许使用的运算符：~ |
- 最大运算次数：7
- 难度：1
*/
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}


/*
- bitXor - 只使用 ~ 和 & 实现 x ^ y
- 示例：bitXor(4, 5) = 1
- 允许使用的运算符：~ &
- 最大运算次数：7
- 难度：1
*/
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}


/*
- samesign - 判断两个整数是否具有相同的符号。
- 0 既不是正数，也不是负数。
- 示例：samesign(0, 1) = 0，samesign(0, 0) = 1
-
   samesign(-4, -5) = 1，samesign(-4, 5) = 0

- 允许使用的运算符：>> << ! ^ && if else &
- 最大运算次数：12
- 难度：2
-
- 参数：
- x - 第一个整数
- y - 第二个整数
-
- 返回值：
- 如果 x 和 y 符号相同，返回 1，否则返回 0。
*/
int samesign(int x, int y) {
    if (!x) {
        return !y;
    }

    if (!y) {
        return 0;
    }

    return !((x >> 31) ^ (y >> 31));
}


/*
- logtwo - 使用位移运算计算一个正整数以 2 为底的对数。
- （可以参考 bitCount 的思路）
- 注意：可以假设 v > 0
- 示例：logtwo(32) = 5
- 允许使用的运算符：> < >> << |
- 最大运算次数：25
- 难度：4
*/
int logtwo(int v) {
    int result = 0;
    int shift;

    shift = (v > 0xFFFF) << 4;
    v = v >> shift;
    result = result | shift;

    shift = (v > 0xFF) << 3;
    v = v >> shift;
    result = result | shift;

    shift = (v > 0xF) << 2;
    v = v >> shift;
    result = result | shift;

    shift = (v > 0x3) << 1;
    v = v >> shift;
    result = result | shift;

    shift = v > 0x1;
    result = result | shift;

    return result;
}


/*
- byteSwap - 交换第 n 个字节和第 m 个字节
- 示例：byteSwap(0x12345678, 1, 3) = 0x56341278

   byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD

- 注意：可以假设 0 <= n <= 3，0 <= m <= 3
- 允许使用的运算符：! ~ & ^ | + << >>
- 最大运算次数：17
- 难度：2
*/
int byteSwap(int x, int n, int m) {
    int nseat = n << 3;
    int mseat = m << 3;
    int nnum = (x >> nseat) & 0xFF;
    int mnum = (x >> mseat) & 0xFF;
    int diff = nnum ^ mnum;

    /* 无符号掩码使左移按 32 位无符号规则计算，避免移入符号位时溢出。 */
    return x ^ ((diff & 0xFFu) << nseat) ^ ((diff & 0xFFu) << mseat);
}


/*
- reverse - 将一个 32 位无符号整数的二进制位顺序完全反转。
- 示例：
- reverse(0xFFFF0000) = 0x0000FFFF
- reverse(0x80000000) = 0x1
- reverse(0xA0000000) = 0x5
- 注意：可以假设 unsigned 整数为 32 位。
- 允许使用的运算符：<< | & - + >> for while ! ~
- （可以在这个函数中定义 unsigned 类型变量）
- 最大运算次数：30
- 难度：3
*/
unsigned reverse(unsigned v) {
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    v = (v >> 16) | (v << 16);

    return v;
}


/*
- logicalShift - 将 x 逻辑右移 n 位
- 示例：logicalShift(0x87654321, 4) = 0x08765432
- 注意：可以假设 0 <= n <= 31
- 允许使用的运算符：! ~ & ^ | + << >>
- 最大运算次数：20
- 难度：3
*/
int logicalShift(int x, int n) {
    int mask;
    int zero = !n;

    mask = 0x7FFFFFFF >> (n + ~0 + zero);

    /* n 为 0 时保留原符号位，其余情况只保留逻辑右移后的低位。 */
    return ((x >> n) & mask) | (x & ~0x7FFFFFFF & (~zero + 1));
}


/*
- leftBitCount - 返回从整数最左端（最高位）开始连续出现的 1 的个数。
- 示例：
- leftBitCount(-1) = 32
- leftBitCount(0xFFF0F0F0) = 12
- leftBitCount(0xFE00FF0F) = 7
- 允许使用的运算符：! ~ & ^ | + << >>
- 最大运算次数：50
- 难度：4
*/
int leftBitCount(int x) {
    int n;
    int b;

    /* 原数前导 1 的个数等于取反后前导 0 的个数。 */
    x = ~x;
    b = (!!(x >> 16)) << 4;
    n = b;
    x = x >> b;

    b = (!!(x >> 8)) << 3;
    n = n + b;
    x = x >> b;

    b = (!!(x >> 4)) << 2;
    n = n + b;
    x = x >> b;

    b = (!!(x >> 2)) << 1;
    n = n + b;
    x = x >> b;

    b = !!(x >> 1);
    n = n + b;
    x = x >> b;

    return 32 + ~n + !x;
}


/*
- float_i2f - 返回表达式 (float)x 对应的二进制位表示。
- 返回结果的类型是 unsigned int，
- 但应该把它解释为一个单精度浮点数的二进制位表示。
- 允许使用的运算符：
- if else while for & | ~ + - >> << < > ! ==
- 最大运算次数：30
- 难度：4
*/
unsigned float_i2f(int x) {
    unsigned sign;
    unsigned ux;
    unsigned frac;
    unsigned rest;
    unsigned half;
    int pos;
    int shift;

    if (x == 0) {
        return 0;
    }

    sign = x & 0x80000000;

    ux = x;
    if (x < 0) {
        ux = ~ux + 1;
    }

    pos = 31;

    while (!((ux >> pos) & 1)) {
        pos = pos - 1;
    }

    if (pos < 24) {
        frac = ux << (23 - pos);
    } else {
        shift = pos - 23;
        frac = ux >> shift;
        rest = ux & ((1 << shift) - 1);
        half = 1 << (shift - 1);

        if (rest > (half - (frac & 1))) {
            frac = frac + 1;
        }
    }

    return sign | (((pos + 126) << 23) + frac);
}

/*
- floatScale2 - 返回浮点表达式 2*f 对应的二进制位表示。
- 参数和返回值都使用 unsigned int 类型传递，
- 但实际上应该把它们解释为单精度浮点数的二进制位表示。
- 如果参数是 NaN，则直接返回原参数。
- 允许使用的运算符：
- & >> << | if > < >= <= ! ~ else + ==
- 最大运算次数：30
- 难度：4
*/
unsigned floatScale2(unsigned uf) {
    unsigned sign;
    unsigned exp;
    unsigned frac;

    sign = uf & 0x80000000;
    exp = (uf >> 23) & 0xFF;
    frac = uf & 0x7FFFFF;

    if (exp == 0xFF) {
        return uf;
    }

    if (exp == 0) {
        frac = frac << 1;
        return sign | frac;
    }

    exp = exp + 1;

    if (exp == 0xFF) {
        frac = 0;
    }

    return sign | (exp << 23) | frac;
}


/*
- float64_f2i - 将一个 64 位 IEEE 754 浮点数转换成
- 一个 32 位有符号整数。
- 转换时向 0 方向舍入。
-
- 注意：
- 假设浮点数采用 IEEE 754 表示，
- 整数采用标准二进制补码表示。
-
- 参数：
- uf1 - 64 位浮点数的低 32 位
- uf2 - 64 位浮点数的高 32 位
-
- 返回值：
- 返回转换后的整数；
- 如果发生溢出，返回 0x80000000；
- 如果发生下溢，返回 0。
-
- 允许使用的运算符：
- >> << | & ~ ! + - > < >= <= if else
- 最大运算次数：60
- 难度：3
*/
int float64_f2i(unsigned uf1, unsigned uf2) {
    int exp;
    int e;
    unsigned sign;
    unsigned high;
    unsigned value;

    sign = uf2 >> 31;
    exp = (uf2 >> 20) & 0x7FF;
    e = exp - 1023;

    if (e < 0) {
        return 0;
    }

    if (e > 30) {
        return 0x80000000;
    }

    high = (1 << 20) | (uf2 & 0xFFFFF);

    if (e < 21) {
        value = high >> (20 - e);
    } else {
        value = (high << (e - 20)) | (uf1 >> (52 - e));
    }

    if (sign) {
        return -value;
    }

    return value;
}


/*
- floatPower2 - 返回表达式 2.0^x（即 2.0 的 x 次方）
- 对应的二进制位表示，x 可以是任意 32 位整数。
-
- 返回的 unsigned 值应该与单精度浮点数 2.0^x 的
- 二进制位表示完全相同。
-
- 如果结果太小，连非规格化数（denorm）都无法表示，
- 则返回 0。
- 如果结果太大，则返回正无穷 +INF。
-
- 允许使用的运算符：
- < > <= >= << >> + - & | ~ ! if else &&
- 最大运算次数：30
- 难度：4
*/
unsigned floatPower2(int x) {
    if (x < -149) {
        return 0;
    }

    if (x < -126) {
        return 1 << (x + 149);
    }

    if (x <= 127) {
        return (x + 127) << 23;
    }

    return 0x7F800000;
}
