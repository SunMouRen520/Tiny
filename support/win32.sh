cd ../build
if [ ! -d WIN32 ] ; then
    mkdir WIN32
fi
cd WIN32
cmake -G "Visual Studio 14 2015"  -DCMAKE_PREFIX_PATH="C:/Sys"  -DCMAKE_MODULE_PATH="C:/Sys" --build -DPACKAGE_TESTS=ON -Dgtest_force_shared_crt=TRUE ..\\..
