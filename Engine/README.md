## Game/Engine Publicity

**Project Website**: https://j-ober7.github.io/GGDSite/

## Compilation Instructions
First clone the GGD repo

For the editor/GUI, Pillow for python is required
python3 -m pip install --upgrade pip
python3 -m pip install --upgrade Pillow

For linux, go into bin and run `python3 linuxbuild.py`

For mingw, go into bin and run `sh mingw64build.sh`
NOTE: We encountered an error last minute where python files trying to import it were unable to find it, was only able to reproduce the issue on 1 computer but it could potentially cause problems. This does not impact the linux build.
```Traceback (most recent call last):
  File "game.py", line 4, in <module>
    import mygameengine
ImportError: DLL load failed: The specified module could not be found.
```

Once build is complete, there should be a mygameengine module able to be imported into a .py file. An example of this can be found in game.py

## Project Hieararchy

### ./Engine Directory Organization

- Docs 
    - Source Code Documentation
- Assets
    - Art assets (With the Sub directories music, sound, images, and anything else)
- src
    - source code(.cpp files) The make file or any build scripts that automate the building of your project should reside here.
- include
    - header files(.h and .hpp files)
- lib
    - libraries (.so, .dll, .a, .dylib files). Note this is a good place to put SDL
- bin
    - This is the directory where your built executable(.exe for windows, .app for Mac, or a.out for Linux) and any additional generated files are put after each build.
- ThirdParty
    - Code that you have not written if any.

