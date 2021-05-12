# libgebi
library for random c++ functions (just for reference, not actively used anymore)

## build

```
cd build && cmake ../
make -j10
   # link failure in test_singleton testcase because boost wraps singleton into another singleton, rest works
/usr/bin/ld: CMakeFiles/test_singleton.dir/test_singleton.cpp.o: warning: relocation against `_ZN4gebi9SingletonI4TestNS_12createMeyersENS_9NullMutexEE5lock_E' in read-only section `.text._ZN4gebi9SingletonI4TestNS_12createMeyersENS_9NullMutexEE8instanceEv[_ZN4gebi9SingletonI4TestNS_12createMeyersENS_9NullMutexEE8instanceEv]'
/usr/bin/ld: CMakeFiles/test_singleton.dir/test_singleton.cpp.o: in function `gebi::Singleton<Test, gebi::createMeyers, gebi::NullMutex>::instance()':
test_singleton.cpp:(.text._ZN4gebi9SingletonI4TestNS_12createMeyersENS_9NullMutexEE8instanceEv[_ZN4gebi9SingletonI4TestNS_12createMeyersENS_9NullMutexEE8instanceEv]+0x1b): undefined reference to `gebi::Singleton<Test, gebi::createMeyers, gebi::NullMutex>::lock_'
/usr/bin/ld: CMakeFiles/test_singleton.dir/test_singleton.cpp.o: in function `gebi::Singleton<Test, gebi::createGamma, gebi::NullMutex>::instance()':
test_singleton.cpp:(.text._ZN4gebi9SingletonI4TestNS_11createGammaENS_9NullMutexEE8instanceEv[_ZN4gebi9SingletonI4TestNS_11createGammaENS_9NullMutexEE8instanceEv]+0x1c): undefined reference to `gebi::Singleton<Test, gebi::createGamma, gebi::NullMutex>::lock_'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
```

## test
```
% make test
Running tests...
Test project /home/gebi/my-projects/libgebi/build
    Start 1: test_counter
1/5 Test #1: test_counter .....................   Passed    0.01 sec
    Start 2: test_hash
2/5 Test #2: test_hash ........................   Passed    0.27 sec
    Start 3: test_invsqrt
3/5 Test #3: test_invsqrt .....................   Passed    0.01 sec
    Start 4: test_math
4/5 Test #4: test_math ........................   Passed    0.01 sec
    Start 5: test_singleton
Could not find executable test_singleton
Looked in the following places:
test_singleton
test_singleton
Release/test_singleton
Release/test_singleton
Debug/test_singleton
Debug/test_singleton
MinSizeRel/test_singleton
MinSizeRel/test_singleton
RelWithDebInfo/test_singleton
RelWithDebInfo/test_singleton
Deployment/test_singleton
Deployment/test_singleton
Development/test_singleton
Development/test_singleton
Unable to find executable: test_singleton
5/5 Test #5: test_singleton ...................***Not Run   0.00 sec

80% tests passed, 1 tests failed out of 5

Total Test time (real) =   0.30 sec

The following tests FAILED:
          5 - test_singleton (Not Run)
Errors while running CTest
make: *** [Makefile:103: test] Error 8
```
