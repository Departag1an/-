
1.tasks.josn
    将文件的command值换成自己的g++目录, tasks.josn负责构建编译运行

2.launch.josn
    将文件的preLaunchTask值为tasks.josn中的label, 这样在调试进行之前会先执行tasks任务
    代码我写了两部分, 上面的是用lldb进行调试(Codelldb插件), 注释掉的第二部分的是使用cppdbg
    由于我用cppdbg调试的时候, 运行完毕, 终端console会自动关闭, 而且有些地方也不太一样,所以我用的第一种调试
3.c_cpp_properties.json
    主要是指定c++版本, 指定编译器路径

4.  生成的文件会放在当前目录的output里, 如果不存在这个文件夹会自动生成
    想修改输出目录, 可以修改这部分代码:
    "program": "${workspaceFolder}\\output\\${fileBasenameNoExtension}", 

5.如果想调试的时候额外打开一个终端console进行输入:
    如果是Codelldb:
        在vscode的设置中搜索: Launch: Terminal, 改为external即可
    
