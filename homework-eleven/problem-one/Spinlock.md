fastest when done like this

Average time: 0.00832417

```c++
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  

    pthread_spin_lock(num->spinlock);  
    for (int i = 0; i < 10000; ++i)  
    {  
        num->x++;  
    }  
    pthread_spin_unlock(num->spinlock);  

    return nullptr;  
}  
```
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

```c++
#include <iostream>  
#include <vector>  
#include <pthread.h>  
#include <ctime>  
#include <chrono>  
  
class Number  
{  
private:  
    pthread_spinlock_t* spinlock;  
public:  
    int x = 0;  
  
    Number()  
    {  
        spinlock = new pthread_spinlock_t();  
        pthread_spin_init(spinlock, PTHREAD_PROCESS_PRIVATE);  
    }  
    void inc()  
    {  
        pthread_spin_lock(spinlock);  
        x++;  
        pthread_spin_unlock(spinlock);  
    }  
  
    ~Number()  
    {  
        pthread_spin_destroy(spinlock);  
        delete spinlock;  
    }  
};  
  
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  
    // lock  
    for (int i = 0; i < 10000; ++i)  
    {  
        num->inc();  
    }  
    // unlock  
    return nullptr;  
}  
  
int main(int argc, char** argv)  
{  
    double res = 0;  
    for(int i = 0; i < 100; ++i)  
    {  
        Number *num = new Number();  
        num->x = 2;  
        std::vector <pthread_t> tids(20);  
  
        auto start_time = std::chrono::high_resolution_clock::now();  
  
        for (int i = 0; i < 20; ++i) {  
            pthread_create(&tids[i], NULL, example, (void *) num);  
        }  
  
        for (int i = 0; i < 20; ++i) {  
            pthread_join(tids[i], NULL);  
        }  
  
        auto end_time = std::chrono::high_resolution_clock::now();  
        std::chrono::duration<double> elapsed_time = end_time - start_time;  
  
  
        //std::cout << num->x << std::endl;  
  
        std::cout << i << ": Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;  
        delete num;  
        res+=elapsed_time.count();  
    }  
    std::cout<<std::endl<<"Average time: "<<res/100<<std::endl;  
    return 0;  
}
```

0: Elapsed time: 0.00384677 seconds
1: Elapsed time: 0.187957 seconds
2: Elapsed time: 0.0195697 seconds
3: Elapsed time: 0.00501038 seconds
4: Elapsed time: 0.0301543 seconds
5: Elapsed time: 0.0130787 seconds
6: Elapsed time: 0.00680212 seconds
7: Elapsed time: 0.00446933 seconds
8: Elapsed time: 0.00707756 seconds
9: Elapsed time: 0.0182532 seconds
10: Elapsed time: 0.00777384 seconds
11: Elapsed time: 0.00801416 seconds
12: Elapsed time: 0.0066152 seconds
13: Elapsed time: 0.00827278 seconds
14: Elapsed time: 0.0142281 seconds
15: Elapsed time: 0.00485907 seconds
16: Elapsed time: 0.0320746 seconds
17: Elapsed time: 0.0237288 seconds
18: Elapsed time: 0.044403 seconds
19: Elapsed time: 0.042143 seconds
20: Elapsed time: 0.00594717 seconds
21: Elapsed time: 0.0124127 seconds
22: Elapsed time: 0.0062424 seconds
23: Elapsed time: 0.00756083 seconds
24: Elapsed time: 0.00814415 seconds
25: Elapsed time: 0.0042764 seconds
26: Elapsed time: 0.0528925 seconds
27: Elapsed time: 0.0049051 seconds
28: Elapsed time: 0.0417556 seconds
29: Elapsed time: 0.00396188 seconds
30: Elapsed time: 0.00538058 seconds
31: Elapsed time: 0.00992136 seconds
32: Elapsed time: 0.00868201 seconds
33: Elapsed time: 0.00392634 seconds
34: Elapsed time: 0.0188381 seconds
35: Elapsed time: 0.00498844 seconds
36: Elapsed time: 0.00459464 seconds
37: Elapsed time: 0.0606961 seconds
38: Elapsed time: 0.00620212 seconds
39: Elapsed time: 0.00860148 seconds
40: Elapsed time: 0.00899613 seconds
41: Elapsed time: 0.0291941 seconds
42: Elapsed time: 0.00783491 seconds
43: Elapsed time: 0.00723415 seconds
44: Elapsed time: 0.0153228 seconds
45: Elapsed time: 0.0665826 seconds
46: Elapsed time: 0.00363136 seconds
47: Elapsed time: 0.00572844 seconds
48: Elapsed time: 0.0171922 seconds
49: Elapsed time: 0.00326827 seconds
50: Elapsed time: 0.00338209 seconds
51: Elapsed time: 0.00598025 seconds
52: Elapsed time: 0.00469148 seconds
53: Elapsed time: 0.00377979 seconds
54: Elapsed time: 0.00820173 seconds
55: Elapsed time: 0.00765202 seconds
56: Elapsed time: 0.0159661 seconds
57: Elapsed time: 0.00553137 seconds
58: Elapsed time: 0.0206906 seconds
59: Elapsed time: 0.00658751 seconds
60: Elapsed time: 0.0156395 seconds
61: Elapsed time: 0.00513474 seconds
62: Elapsed time: 0.00450768 seconds
63: Elapsed time: 0.20084 seconds
64: Elapsed time: 0.0321309 seconds
65: Elapsed time: 0.0086382 seconds
66: Elapsed time: 0.00905659 seconds
67: Elapsed time: 0.0510569 seconds
68: Elapsed time: 0.00537121 seconds
69: Elapsed time: 0.00551983 seconds
70: Elapsed time: 0.0154125 seconds
71: Elapsed time: 0.00541803 seconds
72: Elapsed time: 0.00874904 seconds
73: Elapsed time: 0.0190639 seconds
74: Elapsed time: 0.00505299 seconds
75: Elapsed time: 0.00536453 seconds
76: Elapsed time: 0.00471121 seconds
77: Elapsed time: 0.0380397 seconds
78: Elapsed time: 0.00520282 seconds
79: Elapsed time: 0.00514401 seconds
80: Elapsed time: 0.155641 seconds
81: Elapsed time: 0.0045569 seconds
82: Elapsed time: 0.143134 seconds
83: Elapsed time: 0.00579523 seconds
84: Elapsed time: 0.00926618 seconds
85: Elapsed time: 0.00794777 seconds
86: Elapsed time: 0.00918507 seconds
87: Elapsed time: 0.0079858 seconds
88: Elapsed time: 0.0108462 seconds
89: Elapsed time: 0.0172768 seconds
90: Elapsed time: 0.0517772 seconds
91: Elapsed time: 0.00387255 seconds
92: Elapsed time: 0.0288681 seconds
93: Elapsed time: 0.00634749 seconds
94: Elapsed time: 0.00501769 seconds
95: Elapsed time: 0.0220203 seconds
96: Elapsed time: 0.0223627 seconds
97: Elapsed time: 0.00650039 seconds
98: Elapsed time: 0.0164423 seconds
99: Elapsed time: 0.0315427 seconds

Average time: 0.0203215

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

```c++
#include <iostream>  
#include <vector>  
#include <pthread.h>  
#include <ctime>  
#include <chrono>  
  
class Number  
{  
public:  
    pthread_spinlock_t* spinlock;  
  
    int x = 0;  
  
    Number()  
    {  
        spinlock = new pthread_spinlock_t();  
        pthread_spin_init(spinlock, PTHREAD_PROCESS_PRIVATE);  
    }  
  
    ~Number()  
    {  
        pthread_spin_destroy(spinlock);  
        delete spinlock;  
    }  
};  
  
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  
    // lock  
    for (int i = 0; i < 10000; ++i)  
    {  
        pthread_spin_lock(num->spinlock);  
        num->x++;  
        pthread_spin_unlock(num->spinlock);  
    }  
    // unlock  
    return nullptr;  
}  
  
int main(int argc, char** argv)  
{  
    double res = 0;  
    for(int i = 0; i < 100; ++i)  
    {  
        Number *num = new Number();  
        num->x = 2;  
        std::vector <pthread_t> tids(20);  
  
        auto start_time = std::chrono::high_resolution_clock::now();  
  
        for (int i = 0; i < 20; ++i) {  
            pthread_create(&tids[i], NULL, example, (void *) num);  
        }  
  
        for (int i = 0; i < 20; ++i) {  
            pthread_join(tids[i], NULL);  
        }  
  
        auto end_time = std::chrono::high_resolution_clock::now();  
        std::chrono::duration<double> elapsed_time = end_time - start_time;  
  
  
        //std::cout << num->x << std::endl;  
  
        std::cout << i << ": Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;  
        delete num;  
        res+=elapsed_time.count();  
    }  
    std::cout<<std::endl<<"Average time: "<<res/100<<std::endl;  
    return 0;  
}
}
```

0: Elapsed time: 0.0080342 seconds
1: Elapsed time: 0.0363833 seconds
2: Elapsed time: 0.0200578 seconds
3: Elapsed time: 0.021756 seconds
4: Elapsed time: 0.00519556 seconds
5: Elapsed time: 0.175476 seconds
6: Elapsed time: 0.00315346 seconds
7: Elapsed time: 0.00361844 seconds
8: Elapsed time: 0.00684023 seconds
9: Elapsed time: 0.00611204 seconds
10: Elapsed time: 0.0144803 seconds
11: Elapsed time: 0.00526216 seconds
12: Elapsed time: 0.0550342 seconds
13: Elapsed time: 0.00689408 seconds
14: Elapsed time: 0.0116088 seconds
15: Elapsed time: 0.022 seconds
16: Elapsed time: 0.00363015 seconds
17: Elapsed time: 0.00570641 seconds
18: Elapsed time: 0.0041064 seconds
19: Elapsed time: 0.0104381 seconds
20: Elapsed time: 0.00361203 seconds
21: Elapsed time: 0.0138983 seconds
22: Elapsed time: 0.0431379 seconds
23: Elapsed time: 0.00342247 seconds
24: Elapsed time: 0.0093773 seconds
25: Elapsed time: 0.041328 seconds
26: Elapsed time: 0.0243024 seconds
27: Elapsed time: 0.00717042 seconds
28: Elapsed time: 0.0347662 seconds
29: Elapsed time: 0.0388916 seconds
30: Elapsed time: 0.00339354 seconds
31: Elapsed time: 0.00459018 seconds
32: Elapsed time: 0.0146055 seconds
33: Elapsed time: 0.00613776 seconds
34: Elapsed time: 0.00515657 seconds
35: Elapsed time: 0.00520833 seconds
36: Elapsed time: 0.0130928 seconds
37: Elapsed time: 0.00976828 seconds
38: Elapsed time: 0.009419 seconds
39: Elapsed time: 0.014669 seconds
40: Elapsed time: 0.0323784 seconds
41: Elapsed time: 0.00543122 seconds
42: Elapsed time: 0.00826403 seconds
43: Elapsed time: 0.00682098 seconds
44: Elapsed time: 0.0156758 seconds
45: Elapsed time: 0.0128247 seconds
46: Elapsed time: 0.00381037 seconds
47: Elapsed time: 0.0666823 seconds
48: Elapsed time: 0.0517428 seconds
49: Elapsed time: 0.00963765 seconds
50: Elapsed time: 0.00679189 seconds
51: Elapsed time: 0.00491138 seconds
52: Elapsed time: 0.00535708 seconds
53: Elapsed time: 0.0182582 seconds
54: Elapsed time: 0.0287511 seconds
55: Elapsed time: 0.0131602 seconds
56: Elapsed time: 0.00575506 seconds
57: Elapsed time: 0.0188005 seconds
58: Elapsed time: 0.0122032 seconds
59: Elapsed time: 0.00547953 seconds
60: Elapsed time: 0.00499848 seconds
61: Elapsed time: 0.0066563 seconds
62: Elapsed time: 0.00783846 seconds
63: Elapsed time: 0.0198075 seconds
64: Elapsed time: 0.00741524 seconds
65: Elapsed time: 0.00513383 seconds
66: Elapsed time: 0.0411792 seconds
67: Elapsed time: 0.00865323 seconds
68: Elapsed time: 0.00342897 seconds
69: Elapsed time: 0.00564309 seconds
70: Elapsed time: 0.0299431 seconds
71: Elapsed time: 0.00919077 seconds
72: Elapsed time: 0.0145363 seconds
73: Elapsed time: 0.0347489 seconds
74: Elapsed time: 0.0429912 seconds
75: Elapsed time: 0.00518491 seconds
76: Elapsed time: 0.00437832 seconds
77: Elapsed time: 0.00574013 seconds
78: Elapsed time: 0.00671673 seconds
79: Elapsed time: 0.00419733 seconds
80: Elapsed time: 0.0325212 seconds
81: Elapsed time: 0.0096876 seconds
82: Elapsed time: 0.00399249 seconds
83: Elapsed time: 0.0701801 seconds
84: Elapsed time: 0.0350777 seconds
85: Elapsed time: 0.00900485 seconds
86: Elapsed time: 0.0398415 seconds
87: Elapsed time: 0.0061397 seconds
88: Elapsed time: 0.00433865 seconds
89: Elapsed time: 0.00690284 seconds
90: Elapsed time: 0.00415158 seconds
91: Elapsed time: 0.0046743 seconds
92: Elapsed time: 0.0231061 seconds
93: Elapsed time: 0.00683369 seconds
94: Elapsed time: 0.0320641 seconds
95: Elapsed time: 0.0214181 seconds
96: Elapsed time: 0.0481821 seconds
97: Elapsed time: 0.0132452 seconds
98: Elapsed time: 0.0189762 seconds
99: Elapsed time: 0.016715 seconds

Average time: 0.0173991



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


```c++
#include <iostream>  
#include <vector>  
#include <pthread.h>  
#include <ctime>  
#include <chrono>  
  
class Number  
{  
public:  
    pthread_spinlock_t* spinlock;  
  
    int x = 0;  
  
    Number()  
    {  
        spinlock = new pthread_spinlock_t();  
        pthread_spin_init(spinlock, PTHREAD_PROCESS_PRIVATE);  
    }  
  
    ~Number()  
    {  
        pthread_spin_destroy(spinlock);  
        delete spinlock;  
    }  
};  
  
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  

    pthread_spin_lock(num->spinlock);  
    for (int i = 0; i < 10000; ++i)  
    {  
        num->x++;  
    }  
    pthread_spin_unlock(num->spinlock);  

    return nullptr;  
}  
  
int main(int argc, char** argv)  
{  
    double res = 0;  
    for(int i = 0; i < 100; ++i)  
    {  
        Number *num = new Number();  
        num->x = 2;  
        std::vector <pthread_t> tids(20);  
  
        auto start_time = std::chrono::high_resolution_clock::now();  
  
        for (int i = 0; i < 20; ++i) {  
            pthread_create(&tids[i], NULL, example, (void *) num);  
        }  
  
        for (int i = 0; i < 20; ++i) {  
            pthread_join(tids[i], NULL);  
        }  
  
        auto end_time = std::chrono::high_resolution_clock::now();  
        std::chrono::duration<double> elapsed_time = end_time - start_time;  
  
  

  
        std::cout << i << ": Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;  
        delete num;  
        res+=elapsed_time.count();  
    }  
    std::cout<<std::endl<<"Average time: "<<res/10<<std::endl;  
    return 0;  
}
```



0: Elapsed time: 0.00196615 seconds
1: Elapsed time: 0.00245872 seconds
2: Elapsed time: 0.00175967 seconds
3: Elapsed time: 0.00540964 seconds
4: Elapsed time: 0.0056704 seconds
5: Elapsed time: 0.00420271 seconds
6: Elapsed time: 0.0194939 seconds
7: Elapsed time: 0.00321794 seconds
8: Elapsed time: 0.00328751 seconds
9: Elapsed time: 0.00120977 seconds
10: Elapsed time: 0.0114344 seconds
11: Elapsed time: 0.0240661 seconds
12: Elapsed time: 0.00190476 seconds
13: Elapsed time: 0.00663442 seconds
14: Elapsed time: 0.00128439 seconds
15: Elapsed time: 0.0160139 seconds
16: Elapsed time: 0.00184308 seconds
17: Elapsed time: 0.0129934 seconds
18: Elapsed time: 0.00153099 seconds
19: Elapsed time: 0.00278112 seconds
20: Elapsed time: 0.00103988 seconds
21: Elapsed time: 0.0389174 seconds
22: Elapsed time: 0.00108707 seconds
23: Elapsed time: 0.00208455 seconds
24: Elapsed time: 0.00217901 seconds
25: Elapsed time: 0.00187967 seconds
26: Elapsed time: 0.00176078 seconds
27: Elapsed time: 0.00188217 seconds
28: Elapsed time: 0.00135833 seconds
29: Elapsed time: 0.00160351 seconds
30: Elapsed time: 0.005454 seconds
31: Elapsed time: 0.015933 seconds
32: Elapsed time: 0.0023006 seconds
33: Elapsed time: 0.0019203 seconds
34: Elapsed time: 0.0151482 seconds
35: Elapsed time: 0.00207638 seconds
36: Elapsed time: 0.00148843 seconds
37: Elapsed time: 0.00437835 seconds
38: Elapsed time: 0.00536205 seconds
39: Elapsed time: 0.00263856 seconds
40: Elapsed time: 0.00358977 seconds
41: Elapsed time: 0.00123556 seconds
42: Elapsed time: 0.00152302 seconds
43: Elapsed time: 0.0105035 seconds
44: Elapsed time: 0.0634492 seconds
45: Elapsed time: 0.0193914 seconds
46: Elapsed time: 0.0157877 seconds
47: Elapsed time: 0.00228793 seconds
48: Elapsed time: 0.0372783 seconds
49: Elapsed time: 0.00218777 seconds
50: Elapsed time: 0.00513088 seconds
51: Elapsed time: 0.02975 seconds
52: Elapsed time: 0.00292181 seconds
53: Elapsed time: 0.00360901 seconds
54: Elapsed time: 0.00110082 seconds
55: Elapsed time: 0.0243671 seconds
56: Elapsed time: 0.00627499 seconds
57: Elapsed time: 0.00362829 seconds
58: Elapsed time: 0.00543831 seconds
59: Elapsed time: 0.00797843 seconds
60: Elapsed time: 0.00302763 seconds
61: Elapsed time: 0.0047435 seconds
62: Elapsed time: 0.0118229 seconds
63: Elapsed time: 0.0081349 seconds
64: Elapsed time: 0.00168319 seconds
65: Elapsed time: 0.0321934 seconds
66: Elapsed time: 0.00208391 seconds
67: Elapsed time: 0.0146343 seconds
68: Elapsed time: 0.023189 seconds
69: Elapsed time: 0.00297491 seconds
70: Elapsed time: 0.00888235 seconds
71: Elapsed time: 0.00327259 seconds
72: Elapsed time: 0.00141869 seconds
73: Elapsed time: 0.0124088 seconds
74: Elapsed time: 0.00550026 seconds
75: Elapsed time: 0.0178588 seconds
76: Elapsed time: 0.00319007 seconds
77: Elapsed time: 0.0354558 seconds
78: Elapsed time: 0.0218613 seconds
79: Elapsed time: 0.00124207 seconds
80: Elapsed time: 0.0176805 seconds
81: Elapsed time: 0.00397316 seconds
82: Elapsed time: 0.00101113 seconds
83: Elapsed time: 0.010934 seconds
84: Elapsed time: 0.00203543 seconds
85: Elapsed time: 0.00259662 seconds
86: Elapsed time: 0.00375663 seconds
87: Elapsed time: 0.00147139 seconds
88: Elapsed time: 0.00182002 seconds
89: Elapsed time: 0.00177876 seconds
90: Elapsed time: 0.00111345 seconds
91: Elapsed time: 0.00161966 seconds
92: Elapsed time: 0.00196742 seconds
93: Elapsed time: 0.00122081 seconds
94: Elapsed time: 0.00582141 seconds
95: Elapsed time: 0.0156093 seconds
96: Elapsed time: 0.0421917 seconds
97: Elapsed time: 0.00170646 seconds
98: Elapsed time: 0.00349346 seconds
99: Elapsed time: 0.00794813 seconds

Average time: 0.00832417


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
