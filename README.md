# Software Design 2021年2月号 ディープラーニングではじめるソフトウェア高速化入門 第4回 サンプルコード

## 概要

Software Design 2021年2月号掲載の「ディープラーニングではじめるソフトウェア高速化入門 第4回」のサンプルコードです

## 動作確認環境

* Ubuntu 18.04 LTS
* g++ 7.5.0
* libgomp1 8.4.0

## ビルド方法

* makeコマンドを実行すると、以下の4つのプログラムがビルドされます
    * relu
    * conv_multi
    * conv_lock
    * conv_multi_assign

## 各プログラムの説明と実行方法

### ReLU関数 (relu)

* ReLU関数の並列化前のコードと並列化後のコードを実行します
* Aの幅と高さを引数に与えると実行できます
    * (例)Aの大きさが1024x512で実行する場合

```
$ ./relu 1024 512
```

### 畳み込み演算 (conv_multi, conv_lock, conv_multi_assign)

* 畳み込み演算の各並列化方法と、並列化前のコードを実行します。それぞれの意味については記事をご参照ください。
    * conv_multi: 並列化後？
    * conv_multi_lock: 並列化+排他制御使用版
    * conv_multi_assign: 並列化+排他制御不使用版
* いずれのファイルもAとBの幅と高さおよびストライド幅を引数に与えると実行できます
    * (例)Aの大きさが256x128、Bの大きさが11x7、ストライド幅が1でconv_multiを実行する場合

```
$ ./conv_multi 256 128 11 7 1
```

## ソースコードの内容

|ファイル名|内容|
|:----|:---|
|relu.cpp|reluプログラム本体|
|conv_multi.cpp|conv_multiプログラム本体|
|conv_multi_lock.cpp|conv_multi_lockプログラム本体|
|conv_multi_assign.cpp|conv_multi_assignプログラム本体|
|conv_single.hpp|畳み込み演算の並列化前コード|
|test.hpp|テストコード|
|matrix.hpp|行列用クラス|
|timer.hpp|時間計測用関数|

## 作者

* 松宮 遼 (株式会社フィックスターズ)

## ライセンス

* Apache License 2.0
