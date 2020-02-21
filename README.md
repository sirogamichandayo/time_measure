# stopWatch

 
グラフ表示が出来る時間計測ライブラリです。`stopWatch.h`を加えるだけですべての機能が使えます。
 
# Features
 
* 時間計測(折れ線、棒、ネスト可能)
* 結果のグラフ表示、保存
 
# Requirement
 
* python2.7 library(3.6ならエラーが出ます)
* c++17
# Usage

## テストの実行法
 
```bash
$ mkdir time_measure
$ cd time_measure
$ git clone https://github.com/sirogamiemacs/time_measure.git
$ cd time_measure
$ mkdir build
$ cd build
$ cmake ..
$ make 
$ cd test
```
**折れ線グラフ(表示)**
```
$ ./measure_test each
```
![Image description](https://github.com/sirogamiemacs/time_measure/blob/master/img/plot_test.png)

**棒グラフ(表示)**
```
$ ./measure_test ave
```
![Image description](https://github.com/sirogamiemacs/time_measure/blob/master/img/bar_test.png)

**折れ線グラフ(保存)**
```bash
$ ./measure_test each each_
[LOG] (<YOUR DIR>/measure_time/test/../include/stopWatch.h:169) from save_file()
    save in each_.png // each_.pngとしてグラフが保存されました。
```

**折れ線グラフ(保存)**
```bash
$ ./measure_test ave ave_
[LOG] (<YOUR DIR>/measure_time/test/../include/stopWatch.h:169) from save_file()
    save in ave_.png // ave_.pngとしてグラフが保存されました。
```

## 実際の使用例

```bash
$ tree
```
```
.
├── measure_time
│   ├── matplotlibcpp.h
│   └── stopWatch.h
└── test.cpp
```

```test.cpp
// test.cpp
#include <thread>
#include <chrono>
#include "measure_time/stopWatch.h"

using namespace std;
using namespace std::chrono;

int main()
{
    // initialize    
    // 必須。これですべてのストップウォッチを管理する。
    stopWatchController timer_con; 
    // 必須。グラフの形式を設定する。
    // 今の所
    // stopwatch::BAR -> 棒グラフ
    // stopwatch::PLOT -> 折れ線グラフ
    // の２つのみです。
    timer_con.set_format(stopwatch::BAR);
    // 任意。タイトルの設定
    timer_con.set_title_name("compare"); 
    // 任意。ファイル名の設定。この関数を呼び出すとファイルにグラフが保存される様になる。(表示はされなくなる)
    // timer_con.set_file_name("test");

    // 処理ごとのタイマーを作成します。引数にラベルを指定し、返り値を用いてタイマーを制御します。
    unsigned const int PROCESS1 = timer_con.new_timer("process1");
    unsigned const int PROCESS2 = timer_con.new_timer("process2");
    unsigned const int PROCESS3 = timer_con.new_timer("process3");
    unsigned const int PROCESS4 = timer_con.new_timer("process4");

    
    // 時間計測。下の形が基本になる。複数回計測した際は自動的に平均が計算されます。
    // timer.start(TIMER);
    // process
    // timer.lap(TIMER);
    steady_clock::time_point t1, t2;
    for (int i = 0; i < 10; ++i)
    {
        //=======PROCESS1===
        timer_con.start(PROCESS1);
        this_thread::sleep_for(milliseconds(100));
        timer_con.lap(PROCESS1);
        //=======PROCESS2=============================
        timer_con.start(PROCESS2);
        //=======PROCESS3===
        timer_con.start(PROCESS3);
        this_thread::sleep_for(milliseconds(100));
        timer_con.lap(PROCESS3);
        //=======PROCESS3===
        //=======PROCESS4===
        timer_con.start(PROCESS4);
        this_thread::sleep_for(milliseconds(200));
        timer_con.lap(PROCESS4);
        //=======PROCESS4===
        this_thread::sleep_for(milliseconds(100));
        timer_con.lap(PROCESS2);
        //=======PROCESS2=============================
    }
}
```
```
$ g++ -o test test.cpp -lpython2.7
$ ./test
```
![Image description](https://github.com/sirogamiemacs/time_measure/blob/master/img/Figure_1.png?raw=true
)

`timer_con.set_format(stopwatch::BAR);` -> `timer_con.set_format(stopwatch::PLOT);`
に変更してコンパイル、実行


![Image description](https://github.com/sirogamiemacs/time_measure/blob/master/img/test_bar2.png?raw=true
)

 
# License
[MIT license](https://en.wikipedia.org/wiki/MIT_License).
 
