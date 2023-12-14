faster when done like this

Average time: 0.00441593

```c++
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  
    // lock  
    sem_wait(num->semaphore);  
    for (int i = 0; i < 10000; ++i)  
    {  
        num->x++;  
    }  
    sem_post(num->semaphore);  
    // unlock  
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
#include <semaphore.h>  
  
class Number  
{  
private:  
    sem_t* semaphore;  
public:  
    int x = 0;  
  
    Number()  
    {  
        semaphore = new sem_t();  
        sem_init(semaphore, 0, 1);  
    }  
    void inc()  
    {  
        sem_wait(semaphore);  
        x++;  
        sem_post(semaphore);  
    }  
  
    ~Number()  
    {  
        sem_destroy(semaphore);  
        delete semaphore;  
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

0: Elapsed time: 0.0183274 seconds
1: Elapsed time: 0.0194894 seconds
2: Elapsed time: 0.00745574 seconds
3: Elapsed time: 0.0181071 seconds
4: Elapsed time: 0.0508072 seconds
5: Elapsed time: 0.0472228 seconds
6: Elapsed time: 0.0280715 seconds
7: Elapsed time: 0.0472951 seconds
8: Elapsed time: 0.0458021 seconds
9: Elapsed time: 0.0476014 seconds
10: Elapsed time: 0.0400275 seconds
11: Elapsed time: 0.0437167 seconds
12: Elapsed time: 0.0530957 seconds
13: Elapsed time: 0.0375232 seconds
14: Elapsed time: 0.0367153 seconds
15: Elapsed time: 0.0588541 seconds
16: Elapsed time: 0.0068758 seconds
17: Elapsed time: 0.0132036 seconds
18: Elapsed time: 0.0757252 seconds
19: Elapsed time: 0.0317372 seconds
20: Elapsed time: 0.0196874 seconds
21: Elapsed time: 0.0170462 seconds
22: Elapsed time: 0.0271487 seconds
23: Elapsed time: 0.0552053 seconds
24: Elapsed time: 0.0177128 seconds
25: Elapsed time: 0.0263857 seconds
26: Elapsed time: 0.0434048 seconds
27: Elapsed time: 0.0246599 seconds
28: Elapsed time: 0.011926 seconds
29: Elapsed time: 0.0357025 seconds
30: Elapsed time: 0.012033 seconds
31: Elapsed time: 0.0103692 seconds
32: Elapsed time: 0.0528431 seconds
33: Elapsed time: 0.0201486 seconds
34: Elapsed time: 0.0200979 seconds
35: Elapsed time: 0.0520567 seconds
36: Elapsed time: 0.0568022 seconds
37: Elapsed time: 0.0316507 seconds
38: Elapsed time: 0.025343 seconds
39: Elapsed time: 0.0149873 seconds
40: Elapsed time: 0.0638374 seconds
41: Elapsed time: 0.0327507 seconds
42: Elapsed time: 0.0316472 seconds
43: Elapsed time: 0.0423869 seconds
44: Elapsed time: 0.00797733 seconds
45: Elapsed time: 0.0106025 seconds
46: Elapsed time: 0.0235756 seconds
47: Elapsed time: 0.0441223 seconds
48: Elapsed time: 0.0240734 seconds
49: Elapsed time: 0.0152955 seconds
50: Elapsed time: 0.0258583 seconds
51: Elapsed time: 0.0281314 seconds
52: Elapsed time: 0.0307563 seconds
53: Elapsed time: 0.0113558 seconds
54: Elapsed time: 0.00758487 seconds
55: Elapsed time: 0.0566376 seconds
56: Elapsed time: 0.0127701 seconds
57: Elapsed time: 0.0196784 seconds
58: Elapsed time: 0.040214 seconds
59: Elapsed time: 0.0562877 seconds
60: Elapsed time: 0.0419827 seconds
61: Elapsed time: 0.0532747 seconds
62: Elapsed time: 0.0555465 seconds
63: Elapsed time: 0.0161747 seconds
64: Elapsed time: 0.00798692 seconds
65: Elapsed time: 0.0119599 seconds
66: Elapsed time: 0.0634954 seconds
67: Elapsed time: 0.0536252 seconds
68: Elapsed time: 0.0132335 seconds
69: Elapsed time: 0.0419696 seconds
70: Elapsed time: 0.0684344 seconds
71: Elapsed time: 0.0394731 seconds
72: Elapsed time: 0.0476178 seconds
73: Elapsed time: 0.0565367 seconds
74: Elapsed time: 0.0484927 seconds
75: Elapsed time: 0.0597762 seconds
76: Elapsed time: 0.00902046 seconds
77: Elapsed time: 0.0695036 seconds
78: Elapsed time: 0.0407659 seconds
79: Elapsed time: 0.0397835 seconds
80: Elapsed time: 0.0613445 seconds
81: Elapsed time: 0.0462662 seconds
82: Elapsed time: 0.0514831 seconds
83: Elapsed time: 0.0118338 seconds
84: Elapsed time: 0.0468119 seconds
85: Elapsed time: 0.0173137 seconds
86: Elapsed time: 0.0421524 seconds
87: Elapsed time: 0.0432501 seconds
88: Elapsed time: 0.0296798 seconds
89: Elapsed time: 0.00924718 seconds
90: Elapsed time: 0.0082813 seconds
91: Elapsed time: 0.00858951 seconds
92: Elapsed time: 0.0246459 seconds
93: Elapsed time: 0.0376687 seconds
94: Elapsed time: 0.0208909 seconds
95: Elapsed time: 0.0329676 seconds
96: Elapsed time: 0.0156783 seconds
97: Elapsed time: 0.0124609 seconds
98: Elapsed time: 0.0114127 seconds
99: Elapsed time: 0.0203995 seconds

Average time: 0.0327944


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

```c++
#include <iostream>  
#include <vector>  
#include <pthread.h>  
#include <ctime>  
#include <chrono>  
#include <semaphore.h>  
  
class Number  
{  
public:  
    sem_t* semaphore;  
  
    int x = 0;  
  
    Number()  
    {  
        semaphore = new sem_t();  
        sem_init(semaphore, 0, 1);  
    }  
//    void inc()  
//    {  
//        sem_wait(semaphore);  
//        x++;  
//        sem_post(semaphore);  
//    }  
  
    ~Number()  
    {  
        sem_destroy(semaphore);  
        delete semaphore;  
    }  
};  
  
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  
    // lock  
    for (int i = 0; i < 10000; ++i)  
    {  
        sem_wait(num->semaphore);  
        num->x++;  
        sem_post(num->semaphore);  
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

0: Elapsed time: 0.0486481 seconds
1: Elapsed time: 0.0267005 seconds
2: Elapsed time: 0.0340959 seconds
3: Elapsed time: 0.0525681 seconds
4: Elapsed time: 0.0428556 seconds
5: Elapsed time: 0.0106142 seconds
6: Elapsed time: 0.0640727 seconds
7: Elapsed time: 0.0087008 seconds
8: Elapsed time: 0.052535 seconds
9: Elapsed time: 0.0600403 seconds
10: Elapsed time: 0.0417775 seconds
11: Elapsed time: 0.0311568 seconds
12: Elapsed time: 0.0871405 seconds
13: Elapsed time: 0.0502311 seconds
14: Elapsed time: 0.0219616 seconds
15: Elapsed time: 0.0490594 seconds
16: Elapsed time: 0.0216299 seconds
17: Elapsed time: 0.0304512 seconds
18: Elapsed time: 0.0073764 seconds
19: Elapsed time: 0.0219818 seconds
20: Elapsed time: 0.0493161 seconds
21: Elapsed time: 0.00775888 seconds
22: Elapsed time: 0.0132417 seconds
23: Elapsed time: 0.0117402 seconds
24: Elapsed time: 0.0239009 seconds
25: Elapsed time: 0.0329147 seconds
26: Elapsed time: 0.0431053 seconds
27: Elapsed time: 0.00841704 seconds
28: Elapsed time: 0.00907159 seconds
29: Elapsed time: 0.0575102 seconds
30: Elapsed time: 0.0224058 seconds
31: Elapsed time: 0.0206908 seconds
32: Elapsed time: 0.0390689 seconds
33: Elapsed time: 0.0180178 seconds
34: Elapsed time: 0.019243 seconds
35: Elapsed time: 0.0308839 seconds
36: Elapsed time: 0.0347718 seconds
37: Elapsed time: 0.0269011 seconds
38: Elapsed time: 0.0288115 seconds
39: Elapsed time: 0.0150828 seconds
40: Elapsed time: 0.00720993 seconds
41: Elapsed time: 0.0330047 seconds
42: Elapsed time: 0.0228643 seconds
43: Elapsed time: 0.043298 seconds
44: Elapsed time: 0.0427417 seconds
45: Elapsed time: 0.0508704 seconds
46: Elapsed time: 0.0467167 seconds
47: Elapsed time: 0.0379331 seconds
48: Elapsed time: 0.043092 seconds
49: Elapsed time: 0.059944 seconds
50: Elapsed time: 0.0479277 seconds
51: Elapsed time: 0.0447052 seconds
52: Elapsed time: 0.0473083 seconds
53: Elapsed time: 0.0535472 seconds
54: Elapsed time: 0.0332723 seconds
55: Elapsed time: 0.0679447 seconds
56: Elapsed time: 0.0402104 seconds
57: Elapsed time: 0.0415432 seconds
58: Elapsed time: 0.0183152 seconds
59: Elapsed time: 0.0113048 seconds
60: Elapsed time: 0.0386102 seconds
61: Elapsed time: 0.047021 seconds
62: Elapsed time: 0.0190409 seconds
63: Elapsed time: 0.07215 seconds
64: Elapsed time: 0.0488472 seconds
65: Elapsed time: 0.0505787 seconds
66: Elapsed time: 0.0422736 seconds
67: Elapsed time: 0.0434702 seconds
68: Elapsed time: 0.0698404 seconds
69: Elapsed time: 0.0515979 seconds
70: Elapsed time: 0.0448916 seconds
71: Elapsed time: 0.0656237 seconds
72: Elapsed time: 0.0436798 seconds
73: Elapsed time: 0.0671996 seconds
74: Elapsed time: 0.0416736 seconds
75: Elapsed time: 0.0287924 seconds
76: Elapsed time: 0.0414936 seconds
77: Elapsed time: 0.0659559 seconds
78: Elapsed time: 0.0424677 seconds
79: Elapsed time: 0.0772775 seconds
80: Elapsed time: 0.0368092 seconds
81: Elapsed time: 0.0141854 seconds
82: Elapsed time: 0.0632482 seconds
83: Elapsed time: 0.0095738 seconds
84: Elapsed time: 0.0284909 seconds
85: Elapsed time: 0.0585695 seconds
86: Elapsed time: 0.0561403 seconds
87: Elapsed time: 0.0662102 seconds
88: Elapsed time: 0.041462 seconds
89: Elapsed time: 0.0184507 seconds
90: Elapsed time: 0.069412 seconds
91: Elapsed time: 0.0407548 seconds
92: Elapsed time: 0.0347107 seconds
93: Elapsed time: 0.0564468 seconds
94: Elapsed time: 0.0365895 seconds
95: Elapsed time: 0.0716529 seconds
96: Elapsed time: 0.0349026 seconds
97: Elapsed time: 0.0362978 seconds
98: Elapsed time: 0.0584074 seconds
99: Elapsed time: 0.0397899 seconds

Average time: 0.039448

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

```c++
#include <iostream>  
#include <vector>  
#include <pthread.h>  
#include <ctime>  
#include <chrono>  
#include <semaphore.h>  
  
class Number  
{  
public:  
    sem_t* semaphore;  
  
    int x = 0;  
  
    Number()  
    {  
        semaphore = new sem_t();  
        sem_init(semaphore, 0, 1);  
    }  
//    void inc()  
//    {  
//        sem_wait(semaphore);  
//        x++;  
//        sem_post(semaphore);  
//    }  
  
    ~Number()  
    {  
        sem_destroy(semaphore);  
        delete semaphore;  
    }  
};  
  
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  
    // lock  
    sem_wait(num->semaphore);  
    for (int i = 0; i < 10000; ++i)  
    {  
        num->x++;  
    }  
    sem_post(num->semaphore);  
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

0: Elapsed time: 0.00166556 seconds
1: Elapsed time: 0.00164323 seconds
2: Elapsed time: 0.00146612 seconds
3: Elapsed time: 0.00178458 seconds
4: Elapsed time: 0.0018758 seconds
5: Elapsed time: 0.01729 seconds
6: Elapsed time: 0.00214202 seconds
7: Elapsed time: 0.00217767 seconds
8: Elapsed time: 0.00210083 seconds
9: Elapsed time: 0.00257979 seconds
10: Elapsed time: 0.00179693 seconds
11: Elapsed time: 0.00402855 seconds
12: Elapsed time: 0.00739929 seconds
13: Elapsed time: 0.00474354 seconds
14: Elapsed time: 0.00307834 seconds
15: Elapsed time: 0.00250411 seconds
16: Elapsed time: 0.00315673 seconds
17: Elapsed time: 0.002173 seconds
18: Elapsed time: 0.00222428 seconds
19: Elapsed time: 0.00209352 seconds
20: Elapsed time: 0.00525808 seconds
21: Elapsed time: 0.0256027 seconds
22: Elapsed time: 0.00881274 seconds
23: Elapsed time: 0.0101488 seconds
24: Elapsed time: 0.00535315 seconds
25: Elapsed time: 0.00407888 seconds
26: Elapsed time: 0.018391 seconds
27: Elapsed time: 0.00275193 seconds
28: Elapsed time: 0.00181619 seconds
29: Elapsed time: 0.00190561 seconds
30: Elapsed time: 0.0164068 seconds
31: Elapsed time: 0.00293597 seconds
32: Elapsed time: 0.00156628 seconds
33: Elapsed time: 0.00176623 seconds
34: Elapsed time: 0.0317931 seconds
35: Elapsed time: 0.00178749 seconds
36: Elapsed time: 0.00348023 seconds
37: Elapsed time: 0.003013 seconds
38: Elapsed time: 0.00181712 seconds
39: Elapsed time: 0.00264535 seconds
40: Elapsed time: 0.00264983 seconds
41: Elapsed time: 0.00224062 seconds
42: Elapsed time: 0.00190217 seconds
43: Elapsed time: 0.00206184 seconds
44: Elapsed time: 0.00156291 seconds
45: Elapsed time: 0.00174574 seconds
46: Elapsed time: 0.00217232 seconds
47: Elapsed time: 0.00218208 seconds
48: Elapsed time: 0.00162703 seconds
49: Elapsed time: 0.00350868 seconds
50: Elapsed time: 0.00189884 seconds
51: Elapsed time: 0.00195508 seconds
52: Elapsed time: 0.0139518 seconds
53: Elapsed time: 0.00276361 seconds
54: Elapsed time: 0.00398046 seconds
55: Elapsed time: 0.00178763 seconds
56: Elapsed time: 0.00743877 seconds
57: Elapsed time: 0.0116743 seconds
58: Elapsed time: 0.00586626 seconds
59: Elapsed time: 0.00300786 seconds
60: Elapsed time: 0.00149297 seconds
61: Elapsed time: 0.00633088 seconds
62: Elapsed time: 0.00226914 seconds
63: Elapsed time: 0.0020492 seconds
64: Elapsed time: 0.0033239 seconds
65: Elapsed time: 0.00157487 seconds
66: Elapsed time: 0.00183081 seconds
67: Elapsed time: 0.00164691 seconds
68: Elapsed time: 0.00435275 seconds
69: Elapsed time: 0.00260359 seconds
70: Elapsed time: 0.00151872 seconds
71: Elapsed time: 0.00199084 seconds
72: Elapsed time: 0.00489965 seconds
73: Elapsed time: 0.00157422 seconds
74: Elapsed time: 0.00350307 seconds
75: Elapsed time: 0.00238001 seconds
76: Elapsed time: 0.00264422 seconds
77: Elapsed time: 0.00312043 seconds
78: Elapsed time: 0.00284468 seconds
79: Elapsed time: 0.00168384 seconds
80: Elapsed time: 0.00702059 seconds
81: Elapsed time: 0.0109858 seconds
82: Elapsed time: 0.00486813 seconds
83: Elapsed time: 0.00576493 seconds
84: Elapsed time: 0.0179555 seconds
85: Elapsed time: 0.00701004 seconds
86: Elapsed time: 0.0035578 seconds
87: Elapsed time: 0.00320343 seconds
88: Elapsed time: 0.00396054 seconds
89: Elapsed time: 0.00175249 seconds
90: Elapsed time: 0.00269601 seconds
91: Elapsed time: 0.00170448 seconds
92: Elapsed time: 0.00199276 seconds
93: Elapsed time: 0.00239175 seconds
94: Elapsed time: 0.00405447 seconds
95: Elapsed time: 0.00155712 seconds
96: Elapsed time: 0.00233842 seconds
97: Elapsed time: 0.00276667 seconds
98: Elapsed time: 0.00558896 seconds
99: Elapsed time: 0.00155614 seconds

Average time: 0.00441593

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////