## 现象
trl+Alt+F1~F6后，显示黑屏。Ctrl+Alt+F7可以正常返回图形模式。

## 原因

通常是由于启动时的分辨率与显卡不兼容导致。

## 解决方法

解决方法是设置Grub为true text-mode启动。

1. 打开终端
> Ctrl+Alt+T

2. 输入以下命令
> sudo sed -i -e 's/#GRUB_TERMINAL/GRUB_TERMINAL/g' /etc/default/grub

3. 更新grub
> sudo update-grub

4. 重启
> sudo reboot
