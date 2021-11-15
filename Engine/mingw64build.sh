# Run with sh mingw64build.sh


COMPILE="g++ -D MINGW -std=c++14 -shared -fPIC -static-libgcc -static-libstdc++ -I./Include/ -I./pybind11/include/ `python3.6 -m pybind11 --includes` ./src/*.cpp -o mygameengine.pyd `python3.6-config --ldflags` -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf  -mwindows -L libwinpthread-1.dll"


echo $COMPILE
echo "-------------------------------------------"
eval $COMPILE
