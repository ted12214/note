Sublime是一款很好用的编辑器，但是在Linux下的中文输入一直让人很纠结，网上流传的解决方法大都比较繁琐，故在此提供一个基于 Fcitx 输入框架相对比较简单的的解决方案：

**Github传送门**

    lyfeyaj/sublime-text-imfix · GitHub，感谢作者lyfeyaj。

**环境**

    Ubuntu/Debian/Linux Mint 均可…
    已安装 Sublime Text 2/3。
    已安装 Fcitx 输入框架并设置为默认输入法。

**具体步骤**

    1. 更新并升级系统为最新：
    sudo apt-get update && sudo apt-get upgrade
    2. 克隆项目到本地，路径任意 :
    git clone https://github.com/lyfeyaj/sublime-text-imfix.git
    3. 在项目路径下运行脚本：
    cd sublime-text-imfix && ./sublime-imfix
    4. 重启后即可在终端中调用Sublime Text 2/3 ，借助Fcitx进行实现中文输入