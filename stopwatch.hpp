#ifndef ___stopwatch_hpp___
#define ___stopwatch_hpp___

#include <ctime>
#include <iostream>


#define rdtscll(val) \
    __asm__ __volatile__ ("rdtsc" : "=A" (val))


namespace gebi
{

struct NullNotifier
{
    void notify(unsigned long long i) {}
};

struct CoutNotifier
{
    void notify(unsigned long long i) { std::cout <<i; }
};


template<typename Notifier = NullNotifier>
class Stopwatch
{
public:
    Stopwatch() : stopped_(false) {
        rdtscll(start_);
    }
    ~Stopwatch() {
        rdtscll(end_);
        if(stopped_)
            return;
        end_ -= start_; //get elapsed time
        notifier.notify(end_);
    }
    unsigned long long stop() {
        rdtscll(end_);
        stopped_ = true;
        return end_ - start_;
    }
    unsigned long long getTime() { return end_ - start_; }

private:
    unsigned long long start_, end_;
    bool stopped_;
    Notifier notifier;
};

}; // end namespace gebi

#endif // __stopwatch_hpp__
