CSIT314 Project

Build Instructions:
    
    * Install httpd, cgicc and zlib

    Linux:
        cgicc:
            $ wget https://ftp.gnu.org/gnu/cgicc/cgicc-3.2.19.tar.gz
            $ tar xzf cgicc-3.2.19.tar.gz
            $ cd cgicc-3.2.19
            $ ./configure
            $ make
            $ sudo make install  

        httpd should be installed by default on your system
        If not look up your OS's instructions for installing
        apache2

        zlib
            Fedora:
            $ sudo dnf install zlib-devel

            apt based systems:
            $ sudo apt-get install zlib1g-dev

To Run:
    
    $ ./run
    
    You'll need super user privileges on your machine
