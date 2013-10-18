ink
===

### 功能
程序分为两个部分，master和slave。
slave以UDP广播的方式寻找master.
master接收到slave的广播查询后，注册这个slave的ip并应答,
slave收到应答后停止广播，并记录应答的ip地址为服务器地址。

### 编译
> make 

