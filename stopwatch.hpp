#ifndef ___stopwatch_hpp___
#define ___stopwatch_hpp___

#include <iostream>

// thx to dietlibc 0.30 and 0.27 test/cycles.c for the amd64 and ppc implementation
#if defined (__i386__)
#define rdtscll(dst) asm volatile ("rdtsc" : "=A" (dst))

#elif defined (__x86_64__)
#define rdtscll(dst) do { \
    uint32_t l, h; \
    asm volatile ("rdtsc" : "=a" (l), "=d" (h)); \
    dst = (((uint64_t)h) << 32) | l; \
} while (0)

#elif defined (__powerpc64__)
#define rdtscll(dst) asm volatile ("mftb %0" : "=r" (dst))

#elif defined (__powerpc__)
#define rdtscll(dst) do { \
    uint32_t chk, tbl, tbu; \
    /* The code below is as suggested in Motorola reference manual for 32 bits PPCs. */ \
    __asm__ __volatile__ ("1: mftbu %0; mftb %1; mftbu %2; cmpw %2,%0; bne 1b" \
        : "=r" (tbu), "=r" (tbl), "=r" (chk) ); \
    dst = ((uint64_t)tbu << 32) | tbl; \
} while (0)

#else
gettimeofday(&a,0);
#endif


namespace gebi
{

// null object (is removed during optimization from compiler)
struct NullNotifier
{
    static void notify(unsigned long long i) { return; }
};

struct CoutNotifier
{
    static void notify(unsigned long long i) { std::cout <<i; }
};


template<typename Notifier = NullNotifier>
class Stopwatch
{
public:
    Stopwatch() : stopped_(false) {
        rdtscll(start_);
    }
    ~Stopwatch() {
        unsigned long long end;
        rdtscll(end);
        if(!stopped_) {
            stopped_ = true;
            start_ = end - start_;
        }
        Notifier::notify(start_);
    }
    unsigned long long stop() {
        unsigned long long end;
        rdtscll(end);
        if(!stopped_) {
            stopped_ = true;
            start_ = end - start_;
        }
        return start_;
    }
    unsigned long long getTime()
    {
        if(!stopped_) {
            unsigned long long end;
            rdtscll(end);
            return end - start_;
        }
        return start_;
    }

private:
    unsigned long long start_;
    bool stopped_;
    //Notifier notifier;
};

}; // end namespace gebi

#endif // __stopwatch_hpp__
