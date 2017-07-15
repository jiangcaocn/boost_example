# build boost
以1.64.0为例, build boost很简单了:

build b2
```
./bootstrap.sh --prefix=/opt/boost
```
会生成 b2 bjam project-config.jam. 

--prefix 作用在 project-config.jam 里, 会在 build 时设置 include 和 lib 的安装目录
```
option.set prefix : /opt/boost ;
option.set exec-prefix : /opt/boost ;
option.set libdir : /opt/boost/lib ;
option.set includedir : /opt/boost/include ;
```
build boost

include 和 build 好的 libs 会安装到之前指定的 folder 中 
```
./b2 install
```
提升 build 速度, 可以制定 build thread number (jobs)
```
./b2 -j8 install
```
gcc5.4 默认是不开启 c++11 的, 某些依赖 c++11 特性的代码不会生效. 部分 lib 依赖 c++11 的功能, 如果不支持此特性, 就不会被编译. 比如 fiber 在没有开启 c++11 支持下就不会被编译.
所以需要打开 c++11 的支持, gcc5.4 下, 只打开 --std=c++11 是不能编译fiber的, 使用 --std=c++14 或者 --std=c++17 可以成功
```
./b2 cxxflags="--std=c++17"  -j8 install
```
b2 常用的 property 还有
```
variant=debug|release   Select the build variant
link=static|shared      Whether to build static or shared libraries
```
在根目录下, 默认 build release 下 static 和 shared

# build one boost library

如果需要单独 build 某 library, 可以在 /libs/***/build/ 下 run b2 进行编译

以 fiber 为例
```
cd libs/fiber/build
../../../b2  cxxflags="--std=c++17" -j8 variant=release link=shared install
```
build 产生的中间文件在 bin.v2
```
cj@ubuntu:/opt/boost_1_64_0/bin.v2/libs/fiber$ tree
.
└── build
    └── gcc-5.4.0
        └── release
            └── threading-multi
                ├── algo
                │   ├── algorithm.o
                 ...
                ├── libboost_fiber.so.1.64.0
                 ...
                └── timed_mutex.o
```
# lean cached cxx11_** result
在 b2 build 开始后, 首先输出的是 configuration checks:
```
Performing configuration checks
    \- 32-bit                   : no  (cached)
    \- 64-bit                   : yes (cached)
    ...
    \- symlinks supported       : yes (cached)
    \- C++11 mutex              : yes (cached)
    \- Boost.Config Feature Check: cxx11_auto_declarations : yes (cached)
    \- Boost.Config Feature Check: cxx11_constexpr : yes (cached)
    ...
```
改变 cxxflags 不会清楚上一次 cached 的 feature check 结果, 这是需要删除 cache 结果
```
rm -rf bin.v2
```
