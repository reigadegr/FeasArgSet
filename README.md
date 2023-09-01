# FeasArgSet
一个可以自定义小米Feas配置的功能 需要设备本身支持小米feas功能 自己写自己设备的feas路径 (开关，fps，scaling a b 的节点) 配置文件位于本模块的config文件夹 path.conf写你的设备的路径 package.conf写需要开启feas的游戏包名，目标帧率等参数
注意，github的release和酷安发到蓝奏云的模块不会随着github代码的更新实时更新，想要使用最新的模块建议git clone https://github.com/reigadegr/FeasArgSet 后，打包Module文件夹的全部文件为zip，使用magisk刷入以更新

***编译***
#环境构建
pkg install clang -y
pkg add ndk-multilib
#clone项目
git clone https://github.com/reigadegr/FeasArgSet --depth 1
cd $(pwd)/FeasArgSet/Build
sh build.sh
***完成***