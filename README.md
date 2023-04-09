<div id="top"></div>
<br />
<div align="center">
<h2 align="center">header_docu_qt</h2>

  <p align="center">
      Create documentation or SBOM SPDX from file header
      <br/>
      (focussed on older libraries which didn't use the docs-as-code approach)
    <br />
    <br />
    <a href="https://github.com/Zheng-Bote/header_docu_qt/issues">Report Bug</a>
    ·
    <a href="https://github.com/Zheng-Bote/header_docu_qt/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#screenshots-and-samples">Screenshots and Samples</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

### About the Project 

**Create documentation or SBOM SPDX from file header (e.g. \*.c[pp], \*.h[pp], ...)**

:arrow_right: <mark>:warning: still under construction :warning:</mark> :arrow_left:

*short description:*

File (header) parser with plug-in support for parser-plugins and writer-plugins 

*description:*

With great respect to Doxygen, JSDoc or DoxDox, but they all reading / parsing the complete textfile.

**For me I just need parsing the first comment block of a single textfile or every textfile with a defined file-extension in a folder, doesn't matter if \*.js, \*.h, \*.hpp or whatever**

_scanned / collected Meta data:_

-   TITLE
-   BRIEF
-   DESC
-   AUTHOR
-   LICENSE
-   VERSION
-   COPYRIGHT
-   SOURCE
-   COMMENT
-   SYNTAX
-   HISTORY
-   DEPENDENCIES
-   FILE_PERM           (file permssions)
-   LAST_MODIFIED       (file last modified)
-   FILE_SIZE           (file size in bytes)
-   FILE_HASH_SHA256    (SHA2-256 filehash)

So, this tool is focussed on older libraries which doesn't use the docs-as-code approach.

### built with

This is yet another version of the commandline tool, extended and written in QT 6.5 C++17.

**There are other, older versions:**

- written in QT5 with C++17 : <a href="https://github.com/Zheng-Bote/header_docu" alt="header_docu QT" title="https://github.com/Zheng-Bote/header_docu">header_docu QT5 C++17</a>

- written in plain C++20 : <a href="https://github.com/Zheng-Bote/header_docu_cpp" alt="header_docu CPP" title="https://github.com/Zheng-Bote/header_docu_cpp">header_docu CPP C++20</a>


### docs-as-code approach:

see:

-   <a href="https://docs-as-co.de/" alt="docs-as-code" title="https://docs-as-co.de/">docs-as-code</a>
-   <a href="https://doctoolchain.org/docToolchain" alt="docToolchain" title="https://doctoolchain.org/docToolchain">docToolchain (user site)</a>
-   <a href="https://github.com/doctoolchain/doctoolchain/" alt="docToolchain dev" title="https://github.com/doctoolchain/doctoolchain/">docToolchain (Github)</a>

<!-- GETTING STARTED -->

## Getting Started

**tested with:**

- GNU/Linux with Kernel 5.15
- g++ 11.3.0


### Prerequisites

-   PC or Laptop with Windows, MacOS or Linux \*\_^
-   installed C++ compiler like g++ or clang++ with C++17 support
-   developer tools with cmake

#### DEPENDENCIES:

**cxxopts**

a lightweight C++ option parser library, supporting the standard GNU style syntax for options. 
https://github.com/jarro2783/cxxopts

**inifile-cpp**

inifile-cpp is a simple and easy to use single header-only ini file en- and decoder for C++. 
https://github.com/Rookfighter/inifile-cpp

**OpenSSL**

OpenSSL - a robust, commercial-grade, full-featured toolkit for general-purpose cryptography and secure communication. 
https://www.openssl.org/

OpenSSL (Library tested: OpenSSL 3.0.2 15 Mar 2022; Linux: openssl-dev) is needed for creating SHA2-256Bit Hashes for strings and files.

### Installation

1. Clone the repo
    ```sh
    git clone https://github.com/Zheng-Bote/header_docu_qt/.git
    ```
2. install
    - not yet implemented

<p align="right">(<a href="#top">back to top</a>)</p>

### configuration and build

#### Linux

1. configure your QT project to C++17 and cmake


<p align="right">(<a href="#top">back to top</a>)</p>

## Usage

### SYNTAX:

```
file header parser
Usage:
  ./header_docu_qt [OPTION...]

  -c, --create    create Inifile
  -d, --dir arg   parse directory <dir>
  -e, --ext arg   write to filetype (depends on Plugin):
                  <.adoc> | <.csv> | <.html> | <.json> | <.md> | <.txt>
  -f, --file arg  parse <pathTo/fileName>
  -i, --ini arg   use Inifile <pathTo/inifile> (default: ./header_docu_qt.ini)
  -l, --listini   list Inifile
  -o, --out arg   output directory <dir>
  -v, --version   Print program and version
  -h, --help      Print help
```

#### EXAMPLES:

```
under construction
```

*default:*
```
under construction
```

### RETURN:

     2023-04-03 18:22:57 : 5 .cpp Files in folder ./src found. Output stored with format md in folder ./header_docu_cpp
     
     exit(0)

### HISTORY:

> | Version | Date       | Developer | Comments                           |
> | ------- | ---------- | --------- | ---------------------------------- |
> | 0.0.0   | 2023-04-07 | RZheng  | created                            |

<!-- ROADMAP -->

## Roadmap:

-   [x] quick and dirty commandline parser (see QT5 C++17)

-   [x] migrate QT commandline to vanilla cxx (see CPP, C++20)

-   [x] create final commandline, plugin-based (this one)

-   [x] create optional md file[s]

-   [x] create optional Github md file[s]

-   [x] create optional ASCIIdoc (adoc) file[s]

-   [x] create optional JSON file[s]

-   [x] create optional csv file[s]

-   [x] create optional HTML5 file[s]

-   [x] get SHA2-256 filehash

-   [x] file last modified time

-   [x] file permissions

-   [x] save output results in separared file[s] or in one file

-   [ ] performance improvements for single outfiles (threaded)

-   [ ] create optional SBOM (spdx) json file[s]

-   [ ] upload optional SBOM (spdx) json to RDBMS

-   [ ] build Linux binary


Maybe a Kanban board will be established (soon)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- LICENSE -->

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->

## Contact

ZHENG Robert Zhèng Bó Tè 郑 伯特

Project Link: [https://github.com/Zheng-Bote/https://github.com/Zheng-Bote/header_docu_qt/](https://github.com/Zheng-Bote/header_docu_qt/)


## Screenshots and Samples

**Default Inifile**

```
[Input]
# folder with files to parse
Dir=/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Inputs
# file extensions to parse
Extensions=*.h, *.hpp, *.c, *.cpp

[Meta]
# file attributes
Attributes=FILE_PERM, LAST_MODIFIED, FILE_SIZE, FILE_HASH_SHA256
# header attributes to parse
Metadata=TITLE, BRIEF, DESC, AUTHOR, LICENSE, VERSION, COPYRIGHT, SOURCE, COMMENT, SYNTAX, HISTORY, DEPENDENCIES

[Output]
# output folder
Dir=/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Outputs
# output type
Filetype=.json
# all parsed results in one single file (true), or one output file for each parsed file (singleFile=false)
singleFile=false

[Plugins]
# plug-ins folder for parser
parserDir=/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/parser
# plug-ins folder for output writer
writerDir=/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/writer
```

**Plugin-Loader**

Plug-In loader-test with errors

```
Loading... "/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/parser/libhtml_plugin.so"
Loaded:  "/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/parser/libhtml_plugin.so"
Plugin Constructed
Could not cast:  "/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/parser/libhtml_plugin.so"
Loading... "/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/parser/test.so"
qt.core.plugin.loader: /home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/parser/test.so: failed to map to memory: Das Argument ist ungültig
Error:  "/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/parser/test.so"  Error:  "The file '/home/zb_bamboo/Documents/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/parser/test.so' is not a valid Qt plugin."
Plugins ParserDir has no valid plugins
program criterias missmatch
Plugin Deconstructed
```


### the end

:vulcan_salute:

<p align="right">(<a href="#top">back to top</a>)</p>
