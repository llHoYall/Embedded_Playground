# Arduino Library Format (rev. 2.1)

## library.properties file format

* name
* version
	+ Version should be semver compliant.
	+ Ex) 1.0.0
* author
* maintainer
* sentence
* paragraph
* category
	+ "Display", "Communication", "Signal Input/Output", "Sensors", "Device Control", "Timing", "Data Storage", Data Processing", "Other"
* url
* architectures
	+ A comma separated list of architectures supported by the library. If the library doesn't contain architecture specific code use "*" to match all architectures.
* dot_a_linkage
* includes

```
# Example

name=Test
version=1.0.0
author=llHoYall <hoya128@gmail.com>
maintainer=llHoYall <hoya128@gmail.com>
sentence=This library is for test.
paragraph=Library format test.
category=Other
url=https://
architectures=avr
includes=test.h
```

## Keywords

### keywords.txt file format

```
##############################
# Syntax Coloring Map for  ExampleLibrary
##############################

##############################
# Datatypes (KEYWORD1)
##############################

Test    KEYWORD1

##############################
# Methods and Functions (KEYWORD2)
##############################

doSomething    KEYWORD2

##############################
# Instances (KEYWORD2)
##############################

##############################
# Constants (LITERAL1
##############################
```

## Layout of Folders and Files

```
├ test/library.properties
├ test/keywords.txt
├ test/src/test.h
├ test/src/test.c
├ test/examples/ex1/ex1.ino
├ test/examples/ex2/ex2.ino
└ test/extras/API_References.pdf
```

## Reference

* [Library Specification](https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification)
