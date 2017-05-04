# CRC Calculator on Qt


## Description

CRC Calculator on Qt based of **[uCRC_t](https://github.com/KoynovStas/CRC_CPP_Class)** C++ class for calculation CRC sizes(width) 1-64 bits.


<p align="center">
<img src="./screenshots/animation.gif" width="694"></img>
</p>



### Features

- CRC for Hex:
	- Any word size
	- Any word separators (useful for insertion of Hex data separated by [,:;#$% ... etc])
	- Reverse words
	- Reverse all data

- CRC for Text:
	- Support encodings + Unicode
	- Support [Unicode byte order mark (BOM)](https://en.wikipedia.org/wiki/Byte_order_mark)
	- Different [format of the end of line](https://en.wikipedia.org/wiki/Newline)
	
- Result:
	- Any format (Dec, Hex, Oct + any base: 2..36)
	- A convenient graphical representation of bits


## Build

```console
qmake
make
```



## License

[BSD-3-Clause](./LICENSE).



## Copyright
Copyright (C) 2016 Koynov Stas - skojnov@yandex.ru
