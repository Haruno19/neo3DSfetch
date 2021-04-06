# neo3DSfetch

neo3DSfetch is a tool similar to neofetch for the Nintendo 3DS (you need homebrew/CFW to run it).
It displays the current time, a cute ascii art and some system info.
neo3DSfetch is highly inspired by [3dsfetch by videah](https://github.com/videah/3dsfetch) (from which I took the ascii art). 



### How it works

To put it simple, it's not as cool as common fetch tools: it does not take the information directly from the system or something. 
There's a `.ini` file it reads information from. 


### How to use

Copy in your SD's `/3ds` folder the `.3dsx` file and the `info.ini` file you find in `/source`.
To edit the displayed info, edit the `info.ini` file; here is the order in which you have to write the info (every single piece of info must go on a new line):

1. `color`
1. `user@host`
1. `Luma version`
1. `3DS Firmware version`
1. `Device`
1. `Screen resolution`
1. `CPU`
1. `GPU`
1. `Memory`

The `color` parameter can be: 
1. `red`
1. `green`
1. `yellow`
1. `blue`
1. `magenta`
1. `cyan`
1. `white`

It must be written in lowercase, if there's anything wrong with your parameter, color will be set to `red`. 
____

For any question, post and issue or contact me on [reddit](https://www.reddit.com/user/Joker_513)! :)
