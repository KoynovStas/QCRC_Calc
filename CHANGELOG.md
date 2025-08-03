# Change Log

[**CRC Calculator**](https://github.com/KoynovStas/QCRC_Calc) on Qt based of [**uCRC_t**](https://github.com/KoynovStas/uCRC_t) C++ class for calculation CRC sizes(width) 1-64 bits.

License: [BSD-3-Clause](./LICENSE).

Copyright(c) 2016, Koynov Stas - skojnov@yandex.ru


---


## [Ver 2.3](https://github.com/KoynovStas/QCRC_Calc/releases/tag/v2.3) (2025-08-03)

### What's New

 - New: update uCRC_t 1.3 -> 2.0
 - Fix: use `std:unique`, `List::fromSet` is deprecated since 5.14
 - Fix: add calc CRC for **empty data** (now it's not error)
 - Fix: del `get_instance` in Application (in Qt 5.15 don't closed process)
 - QML: Fixed runtime warning for Connections style
 - QML: off interactive for SwipeView
 - QML: fixed all warning for qml


[...full changes](https://github.com/KoynovStas/QCRC_Calc/compare/v2.2...v2.3)




## [Ver 2.2](https://github.com/KoynovStas/QCRC_Calc/releases/tag/v2.2) (2017-07-16)

### What's New

 - add cmd --file (calculate crc of file. only in console mode)
 - add cmd text_file (for read text from file)
 - add cmd hex_file  (for read hex from file)
 - add support process in thread
 - add buttons for hide/show extParam/extInfo
 - add checkable buttons Hex,Base,Bits


[...full changes](https://github.com/KoynovStas/QCRC_Calc/compare/v2.1...v2.2)




## [Ver 2.1](https://github.com/KoynovStas/QCRC_Calc/releases/tag/v2.1) (2017-05-18)

### What's New

 - Add support CMD (more details see --help)
 - BitItem: not active bits is disabled (other color)
 - Add unit tests


[...full changes](https://github.com/KoynovStas/QCRC_Calc/compare/v2.0...v2.1)




## [Ver 2.0](https://github.com/KoynovStas/QCRC_Calc/releases/tag/v2.0) (2017-05-07)


### What's New

 - New GUI uses QML and Controls 2.0
 - Since version 2.0 Windows XP is not supported

	
### Added

 - Add to CRC_List CRC-3/GSM
 - Add to CRC_List CRC-4/INTERLAKEN
 - Add to CRC_List CRC-6/GSM
 - Add to CRC_List CRC-7/UMTS
 - Add to CRC_List CRC-8/AUTOSAR
 - Add to CRC_List CRC-8/GSM-A
 - Add to CRC_List CRC-8/GSM-B
 - Add to CRC_List CRC-8/LTE
 - Add to CRC_List CRC-8/OPENSAFETY
 - Add to CRC_List CRC-8/SAE-J1850
 - Add to CRC_List CRC-10/GSM
 - Add to CRC_List CRC-11/UMTS
 - Add to CRC_List CRC-12/GSM
 - Add to CRC_List CRC-14/GSM
 - Add to CRC_List CRC-16/CMS
 - Add to CRC_List CRC-16/GSM
 - Add to CRC_List CRC-16/LJ1200
 - Add to CRC_List CRC-16/OPENSAFETY-A
 - Add to CRC_List CRC-16/OPENSAFETY-B
 - Add to CRC_List CRC-16/PROFIBUS
 - Add to CRC_List CRC-24/BLE
 - Add to CRC_List CRC-24/INTERLAKEN
 - Add to CRC_List CRC-24/LTE-A
 - Add to CRC_List CRC-24/LTE-B
 - Add to CRC_List CRC-30/CDMA
 - Add to CRC_List CRC-32/AUTOSAR
 - Add to CRC_List CRC-64/GO-ISO
 - update ucrc_t to 1.3


### Bug fix

 - Fix: Crc for Text (if have BOM string is not empty)


[...full changes](https://github.com/KoynovStas/QCRC_Calc/compare/v1.0...v2.0)




## [Ver 1.0](https://github.com/KoynovStas/QCRC_Calc/releases/tag/v1.0) (2016-02-10)
