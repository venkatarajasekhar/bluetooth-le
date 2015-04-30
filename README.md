# bluetooth-le
C++ bluetooth le library

There is two main purposes where this library is intended for.
1. To provide easy to use interface to receive sensor Heart rate etc..., the library offers a set of apis to use low level, medium level and high level api
2. To provide easy to use data transfer link between two devices, without client to consern about attribute protocol max payload etc...

The library is allso highly configurable, for scanning filtering there is a simple abstract interface which needs to be implemented
for new gatt service implementation see Heart rate service for exsample

Note for ios users you need to add "Other linker flags" --> -all_load

Goals:

Version 1.x.x : First "Beta" version, only ios/mac xcode/qt support (sorry no linux support for the first version) 
Version 2.x.x : Core functionality should be stable, linux support (and maybe windows too), 
Version 3.x.x : 

