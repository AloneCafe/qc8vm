### qc8vm (Quick CHIP-8 Virtual Machine) ###
#### Quick CHIP-8 虚拟机 ####
* 本程序是一种简单的 CHIP-8 虚拟机的实现，使用 C 和 SDL 编写，这是采用[MIT 许可证](https://mit-license.org)授权的自由软件


#### 构建依赖关系 ####
* 本程序的图形界面调用了 SDL 函数库，需要用户在编译环境下，链接 SDL 函数库（2.0 using zlib license）


#### 从源代码开始 ####
##### 源码目录里，附带了 CMakeLists.txt 文件，在终端上可以使用 CMake 可以进行编译 #####
    
1. 使用 Git 克隆源代码仓库: 
    * ``` git clone https://github.com/yenyuloong/qc8vm.git ```

2. 使用 CMake 构建 makefile:
    * ``` cmake ./CMakeLists.txt ```
    
3. 使用 make 构建源代码:
    * ``` make ```
    

#### 开始运行 ####
* 使用默认的编译参数编译的时候，qc8vm 是程序的可执行文件名，在终端上可以直接运行: 
    * ``` chmod +x ./qc8vm ```
    * ``` ./qc8vm ```

