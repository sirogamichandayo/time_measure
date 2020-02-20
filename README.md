# stopWatch

 
グラフ表示が出来る時間計測ライブラリです。`stopWatch.h`を加えるだけですべての機能が使えます。
 
# Features
 
* 時間計測(ネスト可能)
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
$ ./test/measure_time (コマンドライン引数でファイル名を指定すればそのファイルに保存する、指定しなければ表示のみを行う)
```

## 実際の仕様例

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

 
# License
[MIT license](https://en.wikipedia.org/wiki/MIT_License).
 
