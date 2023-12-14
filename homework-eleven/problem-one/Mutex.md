fastest when done like this, 

Average time: 0.00372663
```c++
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  
  
    // lock  
    pthread_mutex_lock(num->mutex);  
    for (int i = 0; i < 10000; ++i)  
    {  
        num->x++;  
    }  
    // unlock  
    pthread_mutex_unlock(num->mutex);  
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
    pthread_mutex_t* mutex;  
public:  
    int x = 0;  
  
    Number()  
    {  
        mutex = new pthread_mutex_t();  
        pthread_mutex_init(mutex, nullptr);  
    }  
    void inc()  
    {  
        pthread_mutex_lock(mutex);  
        x++;  
        pthread_mutex_unlock(mutex);  
    }  
  
    ~Number()  
    {  
        pthread_mutex_destroy(mutex);  
        delete mutex;  
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

0: Elapsed time: 0.0140707 seconds
1: Elapsed time: 0.0124713 seconds
2: Elapsed time: 0.00981611 seconds
3: Elapsed time: 0.0110586 seconds
4: Elapsed time: 0.0266477 seconds
5: Elapsed time: 0.0195166 seconds
6: Elapsed time: 0.0119707 seconds
7: Elapsed time: 0.013955 seconds
8: Elapsed time: 0.0135643 seconds
9: Elapsed time: 0.00987039 seconds
10: Elapsed time: 0.00969753 seconds
11: Elapsed time: 0.00971849 seconds
12: Elapsed time: 0.0107545 seconds
13: Elapsed time: 0.0105717 seconds
14: Elapsed time: 0.0279479 seconds
15: Elapsed time: 0.00970458 seconds
16: Elapsed time: 0.0101011 seconds
17: Elapsed time: 0.00792754 seconds
18: Elapsed time: 0.0138915 seconds
19: Elapsed time: 0.00984021 seconds
20: Elapsed time: 0.0144628 seconds
21: Elapsed time: 0.0104239 seconds
22: Elapsed time: 0.0116785 seconds
23: Elapsed time: 0.012016 seconds
24: Elapsed time: 0.0257435 seconds
25: Elapsed time: 0.0176451 seconds
26: Elapsed time: 0.0164343 seconds
27: Elapsed time: 0.0144532 seconds
28: Elapsed time: 0.0095199 seconds
29: Elapsed time: 0.0116514 seconds
30: Elapsed time: 0.0219988 seconds
31: Elapsed time: 0.0169017 seconds
32: Elapsed time: 0.026724 seconds
33: Elapsed time: 0.0101235 seconds
34: Elapsed time: 0.00832981 seconds
35: Elapsed time: 0.00848275 seconds
36: Elapsed time: 0.00831242 seconds
37: Elapsed time: 0.0109611 seconds
38: Elapsed time: 0.0103921 seconds
39: Elapsed time: 0.00835001 seconds
40: Elapsed time: 0.0107921 seconds
41: Elapsed time: 0.0120939 seconds
42: Elapsed time: 0.025514 seconds
43: Elapsed time: 0.00893895 seconds
44: Elapsed time: 0.0116614 seconds
45: Elapsed time: 0.0330874 seconds
46: Elapsed time: 0.0121444 seconds
47: Elapsed time: 0.00978245 seconds
48: Elapsed time: 0.00687398 seconds
49: Elapsed time: 0.0123571 seconds
50: Elapsed time: 0.0136554 seconds
51: Elapsed time: 0.00894726 seconds
52: Elapsed time: 0.0249754 seconds
53: Elapsed time: 0.0152966 seconds
54: Elapsed time: 0.0313548 seconds
55: Elapsed time: 0.0129707 seconds
56: Elapsed time: 0.0102055 seconds
57: Elapsed time: 0.0141664 seconds
58: Elapsed time: 0.0126057 seconds
59: Elapsed time: 0.010194 seconds
60: Elapsed time: 0.0208004 seconds
61: Elapsed time: 0.0314676 seconds
62: Elapsed time: 0.0332161 seconds
63: Elapsed time: 0.0236672 seconds
64: Elapsed time: 0.0213758 seconds
65: Elapsed time: 0.0115075 seconds
66: Elapsed time: 0.0111991 seconds
67: Elapsed time: 0.0121352 seconds
68: Elapsed time: 0.0100298 seconds
69: Elapsed time: 0.00913172 seconds
70: Elapsed time: 0.00956242 seconds
71: Elapsed time: 0.0132487 seconds
72: Elapsed time: 0.0238635 seconds
73: Elapsed time: 0.0101838 seconds
74: Elapsed time: 0.00685728 seconds
75: Elapsed time: 0.0158973 seconds
76: Elapsed time: 0.024751 seconds
77: Elapsed time: 0.0133375 seconds
78: Elapsed time: 0.010625 seconds
79: Elapsed time: 0.0131814 seconds
80: Elapsed time: 0.0119736 seconds
81: Elapsed time: 0.0114402 seconds
82: Elapsed time: 0.0302625 seconds
83: Elapsed time: 0.00874768 seconds
84: Elapsed time: 0.0261406 seconds
85: Elapsed time: 0.00974733 seconds
86: Elapsed time: 0.0140484 seconds
87: Elapsed time: 0.0170345 seconds
88: Elapsed time: 0.0127959 seconds
89: Elapsed time: 0.01265 seconds
90: Elapsed time: 0.0106178 seconds
91: Elapsed time: 0.0285543 seconds
92: Elapsed time: 0.0116728 seconds
93: Elapsed time: 0.00939787 seconds
94: Elapsed time: 0.0134148 seconds
95: Elapsed time: 0.0243659 seconds
96: Elapsed time: 0.0106058 seconds
97: Elapsed time: 0.0124523 seconds
98: Elapsed time: 0.012946 seconds
99: Elapsed time: 0.0118018 seconds

Average time: 0.0146203

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
    int x = 0;  
    pthread_mutex_t* mutex;  
  
    Number()  
    {  
        mutex = new pthread_mutex_t();  
        pthread_mutex_init(mutex, nullptr);  
    }  
  
    ~Number()  
    {  
        pthread_mutex_destroy(mutex);  
        delete mutex;  
    }  
};  
  
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  
  
    // lock  
    for (int i = 0; i < 10000; ++i)  
    {  
        pthread_mutex_lock(num->mutex);  
        num->x++;  
        pthread_mutex_unlock(num->mutex);  
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

0: Elapsed time: 0.0101427 seconds
1: Elapsed time: 0.00731425 seconds
2: Elapsed time: 0.00731789 seconds
3: Elapsed time: 0.00921368 seconds
4: Elapsed time: 0.015721 seconds
5: Elapsed time: 0.0137113 seconds
6: Elapsed time: 0.0254393 seconds
7: Elapsed time: 0.0120595 seconds
8: Elapsed time: 0.024447 seconds
9: Elapsed time: 0.0162978 seconds
10: Elapsed time: 0.0156409 seconds
11: Elapsed time: 0.011627 seconds
12: Elapsed time: 0.0125642 seconds
13: Elapsed time: 0.0164628 seconds
14: Elapsed time: 0.0455696 seconds
15: Elapsed time: 0.00930714 seconds
16: Elapsed time: 0.0104538 seconds
17: Elapsed time: 0.0186938 seconds
18: Elapsed time: 0.00953553 seconds
19: Elapsed time: 0.0101169 seconds
20: Elapsed time: 0.00700779 seconds
21: Elapsed time: 0.0108855 seconds
22: Elapsed time: 0.00783548 seconds
23: Elapsed time: 0.00556469 seconds
24: Elapsed time: 0.0127952 seconds
25: Elapsed time: 0.0134211 seconds
26: Elapsed time: 0.0116776 seconds
27: Elapsed time: 0.0240724 seconds
28: Elapsed time: 0.0168158 seconds
29: Elapsed time: 0.0112856 seconds
30: Elapsed time: 0.0207494 seconds
31: Elapsed time: 0.0174334 seconds
32: Elapsed time: 0.00870892 seconds
33: Elapsed time: 0.0119542 seconds
34: Elapsed time: 0.00859094 seconds
35: Elapsed time: 0.00675973 seconds
36: Elapsed time: 0.0429628 seconds
37: Elapsed time: 0.0524059 seconds
38: Elapsed time: 0.0152021 seconds
39: Elapsed time: 0.014272 seconds
40: Elapsed time: 0.0427893 seconds
41: Elapsed time: 0.00841317 seconds
42: Elapsed time: 0.00644366 seconds
43: Elapsed time: 0.00970368 seconds
44: Elapsed time: 0.0104111 seconds
45: Elapsed time: 0.0203861 seconds
46: Elapsed time: 0.0115096 seconds
47: Elapsed time: 0.0125277 seconds
48: Elapsed time: 0.00803218 seconds
49: Elapsed time: 0.00811828 seconds
50: Elapsed time: 0.0256671 seconds
51: Elapsed time: 0.00966759 seconds
52: Elapsed time: 0.00820433 seconds
53: Elapsed time: 0.0123213 seconds
54: Elapsed time: 0.0137612 seconds
55: Elapsed time: 0.0281712 seconds
56: Elapsed time: 0.0140527 seconds
57: Elapsed time: 0.0250727 seconds
58: Elapsed time: 0.0177353 seconds
59: Elapsed time: 0.0218839 seconds
60: Elapsed time: 0.0270155 seconds
61: Elapsed time: 0.01368 seconds
62: Elapsed time: 0.0156935 seconds
63: Elapsed time: 0.027102 seconds
64: Elapsed time: 0.0123302 seconds
65: Elapsed time: 0.0129126 seconds
66: Elapsed time: 0.0109285 seconds
67: Elapsed time: 0.0211891 seconds
68: Elapsed time: 0.00974988 seconds
69: Elapsed time: 0.0157146 seconds
70: Elapsed time: 0.00939536 seconds
71: Elapsed time: 0.0412193 seconds
72: Elapsed time: 0.0138634 seconds
73: Elapsed time: 0.0153497 seconds
74: Elapsed time: 0.013285 seconds
75: Elapsed time: 0.00866406 seconds
76: Elapsed time: 0.0106292 seconds
77: Elapsed time: 0.0348986 seconds
78: Elapsed time: 0.00707711 seconds
79: Elapsed time: 0.0256163 seconds
80: Elapsed time: 0.0225772 seconds
81: Elapsed time: 0.0111667 seconds
82: Elapsed time: 0.0139479 seconds
83: Elapsed time: 0.00964459 seconds
84: Elapsed time: 0.00918155 seconds
85: Elapsed time: 0.0136652 seconds
86: Elapsed time: 0.0366805 seconds
87: Elapsed time: 0.0120849 seconds
88: Elapsed time: 0.00751764 seconds
89: Elapsed time: 0.0131108 seconds
90: Elapsed time: 0.0124893 seconds
91: Elapsed time: 0.00791455 seconds
92: Elapsed time: 0.00786786 seconds
93: Elapsed time: 0.0136374 seconds
94: Elapsed time: 0.0259701 seconds
95: Elapsed time: 0.0449447 seconds
96: Elapsed time: 0.0131314 seconds
97: Elapsed time: 0.0106671 seconds
98: Elapsed time: 0.00968995 seconds
99: Elapsed time: 0.00934635 seconds

Average time: 0.0158846

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
    int x = 0;  
    pthread_mutex_t* mutex;  
  
    Number()  
    {  

        mutex = new pthread_mutex_t();  
        pthread_mutex_init(mutex, nullptr);  
    }  
  
    ~Number()  
    {  
        pthread_mutex_destroy(mutex);  
        delete mutex;  
    }  
};  
  
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  
  
    // lock  
    pthread_mutex_lock(num->mutex);  
    for (int i = 0; i < 10000; ++i)  
    {  
        num->x++;  
    }  
    // unlock  
    pthread_mutex_unlock(num->mutex);  
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

0: Elapsed time: 0.00448384 seconds
1: Elapsed time: 0.00153992 seconds
2: Elapsed time: 0.00203957 seconds
3: Elapsed time: 0.00149754 seconds
4: Elapsed time: 0.00156317 seconds
5: Elapsed time: 0.00151903 seconds
6: Elapsed time: 0.00163547 seconds
7: Elapsed time: 0.00195436 seconds
8: Elapsed time: 0.00142817 seconds
9: Elapsed time: 0.00224373 seconds
10: Elapsed time: 0.00181376 seconds
11: Elapsed time: 0.00212442 seconds
12: Elapsed time: 0.00167102 seconds
13: Elapsed time: 0.0154793 seconds
14: Elapsed time: 0.00194239 seconds
15: Elapsed time: 0.00172964 seconds
16: Elapsed time: 0.00149666 seconds
17: Elapsed time: 0.00196844 seconds
18: Elapsed time: 0.00147913 seconds
19: Elapsed time: 0.00162663 seconds
20: Elapsed time: 0.00151993 seconds
21: Elapsed time: 0.00214483 seconds
22: Elapsed time: 0.00159251 seconds
23: Elapsed time: 0.00659106 seconds
24: Elapsed time: 0.00160176 seconds
25: Elapsed time: 0.0016785 seconds
26: Elapsed time: 0.00154484 seconds
27: Elapsed time: 0.0015482 seconds
28: Elapsed time: 0.00183617 seconds
29: Elapsed time: 0.00255431 seconds
30: Elapsed time: 0.00163023 seconds
31: Elapsed time: 0.00193606 seconds
32: Elapsed time: 0.00118118 seconds
33: Elapsed time: 0.00170689 seconds
34: Elapsed time: 0.00179008 seconds
35: Elapsed time: 0.00141104 seconds
36: Elapsed time: 0.00200453 seconds
37: Elapsed time: 0.0024503 seconds
38: Elapsed time: 0.00147562 seconds
39: Elapsed time: 0.00182864 seconds
40: Elapsed time: 0.00193357 seconds
41: Elapsed time: 0.00157841 seconds
42: Elapsed time: 0.0014317 seconds
43: Elapsed time: 0.00184829 seconds
44: Elapsed time: 0.00140588 seconds
45: Elapsed time: 0.00196835 seconds
46: Elapsed time: 0.00137206 seconds
47: Elapsed time: 0.00161696 seconds
48: Elapsed time: 0.00174786 seconds
49: Elapsed time: 0.00161338 seconds
50: Elapsed time: 0.00165559 seconds
51: Elapsed time: 0.00147505 seconds
52: Elapsed time: 0.00161819 seconds
53: Elapsed time: 0.00157537 seconds
54: Elapsed time: 0.00139945 seconds
55: Elapsed time: 0.00152213 seconds
56: Elapsed time: 0.00131765 seconds
57: Elapsed time: 0.00166391 seconds
58: Elapsed time: 0.00176027 seconds
59: Elapsed time: 0.0017714 seconds
60: Elapsed time: 0.00164769 seconds
61: Elapsed time: 0.00159088 seconds
62: Elapsed time: 0.00158922 seconds
63: Elapsed time: 0.00144871 seconds
64: Elapsed time: 0.00182224 seconds
65: Elapsed time: 0.00169811 seconds
66: Elapsed time: 0.0192143 seconds
67: Elapsed time: 0.00157273 seconds
68: Elapsed time: 0.00168952 seconds
69: Elapsed time: 0.00165766 seconds
70: Elapsed time: 0.00170631 seconds
71: Elapsed time: 0.00164968 seconds
72: Elapsed time: 0.00145654 seconds
73: Elapsed time: 0.00167017 seconds
74: Elapsed time: 0.0357018 seconds
75: Elapsed time: 0.00907653 seconds
76: Elapsed time: 0.00559011 seconds
77: Elapsed time: 0.00766227 seconds
78: Elapsed time: 0.00411744 seconds
79: Elapsed time: 0.00330302 seconds
80: Elapsed time: 0.00159932 seconds
81: Elapsed time: 0.00164833 seconds
82: Elapsed time: 0.00178501 seconds
83: Elapsed time: 0.00173828 seconds
84: Elapsed time: 0.0130861 seconds
85: Elapsed time: 0.00561609 seconds
86: Elapsed time: 0.00602715 seconds
87: Elapsed time: 0.00566708 seconds
88: Elapsed time: 0.0074221 seconds
89: Elapsed time: 0.0369592 seconds
90: Elapsed time: 0.00634148 seconds
91: Elapsed time: 0.00419749 seconds
92: Elapsed time: 0.00408111 seconds
93: Elapsed time: 0.00581953 seconds
94: Elapsed time: 0.00593065 seconds
95: Elapsed time: 0.00418626 seconds
96: Elapsed time: 0.0198932 seconds
97: Elapsed time: 0.00373634 seconds
98: Elapsed time: 0.00380459 seconds
99: Elapsed time: 0.00372015 seconds

Average time: 0.00372663

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



