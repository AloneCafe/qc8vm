## qc8vm (Quick CHIP-8 Virtual Machine) ##
### Quick CHIP-8 虚拟机 ###
* 本程序是一种简单的 CHIP-8 虚拟机的实现，使用 C 和 SDL 编写，这是采用 [MIT 许可证](https://mit-license.org) 授权的自由软件


### 构建依赖关系 ###
* 本程序的图形渲染部分调用了 SDL 2.0 函数库，需要用户在编译环境下安装 [SDL 2.0 函数库](http://www.libsdl.org/download-2.0.php)（2.0 using zlib license）
> archlinux 上可以使用 ``` pacman -Syu sdl2 ``` 安装 SDL2 函数库

> Mac 上可以使用 Homebrew ``` brew install sdl2 ``` 安装 SDL2 函数库

### 从源代码开始 ###
> 源码目录里，附带了 CMakeLists.txt 文件，在终端上可以使用 CMake 可以构建源代码
    
1. 使用 Git 克隆源代码仓库: 
    * ``` git clone https://github.com/yenyuloong/qc8vm.git ```

2. 使用 CMake 构建 makefile:
    * ``` cmake ./CMakeLists.txt ```
    
3. 使用 make 根据 makefile 构建源代码:
    * ``` make ```
    

### 开始运行 ###
* 使用默认的编译参数编译的时候，qc8vm 是程序的可执行文件名，在终端上可以直接运行: 
    * ``` chmod +x ./qc8vm ```
    * ``` ./qc8vm ```

### 关于参数 ###
* 例子: ``` qc8vm -f 1000 -c light -p 20 -d ./PROG```  
        (以1000Hz的主频，亮色主题，每方格20像素，调试模式运行虚拟机)
       

     -f: 指定虚拟机主频，指令数/每秒（默认800Hz）
     -d: 虚拟机运行过程的详细输出（用于调试）
     -c: 颜色主题模式，light（0） 和 dark（1）
     -p: 方格的像素大小，默认为10
     -v: 显示虚拟机程序版本
     -h: 显示帮助

### 键盘控制器映射 ###
* CHIP-8 原生 4 x 4 矩阵键盘，共 16 个按键 (0 ~ F)，在 QWERTY 键盘上分别被映射为如下键位:

| QWERTY | CHIP-8 |
| :---: | :---: |
| 1 | 1 |
| 2 | 2 |
| 3 | 3 |
| 4 | C |
| Q | 4 |
| W | 5 |
| E | 6 |
| R | D |
| A | 7 |
| S | 8 |
| D | 9 |
| F | E |
| Z | A |
| X | 0 |
| C | B |
| V | F |

