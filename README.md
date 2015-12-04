Extrawork
=========
ExtraWork is a module used by classic Battle.net games intended to return system data to the server. It can be utilized for different purposes but most notably, for hack detection. During the connection process, the server sends ExtraWork as a signed [MPQ](https://en.wikipedia.org/wiki/MPQ) that contains a DLL file which exports a function called `ExtraWork`. See the [wiki](https://github.com/xboi209/ExtraWork/wiki) for more details.

Binaries
=========
Pre-compiled binaries are available on the [Releases](https://github.com/xboi209/ExtraWork/releases) page.

Compiling
=========
A C++11 compliant compiler with WinAPI available should be able to compile this project.

License
=========
ExtraWork is released under public domain as specified by [UNLICENSE](http://unlicense.org/).
