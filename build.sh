# !/bin/bash
export PLATFORM_ENV=$(pwd)/platform/linux-x86_64/env-linux-x86_64
QT_PATH="${HOME}/Qt/6.2.4/gcc_64"
BUILD_DIR=_build
INSTALL_PREFIX=_install
BUILD_VERSION="1.0.0"
BUILD_TYPE="Debug"
BUILD_DOC=OFF
BUILD_TEST=ON
BUILD_SHARE=ON
BUILD_CLEAN=NO
CLEAR_CMAKE_CACHE=NO

argument_parser() {
    while getopts "p:b:i:v:q:tfshcxde" opt; do
    case $opt in
        p)
            PLATFORM=$OPTARG
        ;;

        b)
            BUILD_TYPE=$OPTARG
            # For windows cmake --config $CMAKE_CONFIG
            if [ "$BUILD_TYPE" = "release" ]; then 
                CMAKE_CONFIG=Release
            fi
        ;;

        t)
            BUILD_SHARE=OFF
        ;;

        i)
            INSTALL_PREFIX=$OPTARG
        ;;

        v)
            BUILD_VERSION=$OPTARG
        ;;

        q)
            [ -d $OPTARG ] && QT_PATH=$OPTARG
        ;;

        c)
            CLEAR_CMAKE_CACHE=YES
        ;;

        x)
            BUILD_CLEAN=YES
        ;;
        
        d)
            BUILD_DOC=ON
        ;;

        e)
            BUILD_TEST=OFF
        ;;

        h)
            echo "Options:"
            echo "Platform:                 -p <linux/windows/raspi/embedded/stm32mp1>"
            echo "Build type:               -b <debug/release - default: debug>"
            echo "Build static library:     -t <default build share library>"
            echo "Install prefix path:      -i <default: _install>"
            echo "Build document enable:    -d"
            echo "Build test disable        -e"
            echo "Build version:            -v <build version eg: 1.0.1>"
            echo "Clear cmake cache:        -c"
            exit;
        ;;
        esac
    done
}

# Parsing input arguments
argument_parser $@

echo ""
echo "---------------------------------------------------------------"
echo "                 Build qtqml-framework options:"
echo "---------------------------------------------------------------"
echo "- CMAKE_PREFIX_PATH     :  $QT_PATH"
echo "- CMAKE_INSTALL_PREFIX  :  $INSTALL_PREFIX"
echo "- BUILD_VERSION         :  $BUILD_VERSION"
echo "- BUILD_TYPE            :  $BUILD_TYPE"
echo "- BUILD_DOC             :  $BUILD_DOC"
echo "- BUILD_TEST            :  $BUILD_TEST"
echo "- BUILD_SHARED_LIBS     :  $BUILD_SHARE"
echo "- BUILD_CLEAN           :  $BUILD_CLEAN"
echo "- CLEAR_CMAKE_CACHE     :  $CLEAR_CMAKE_CACHE"
echo "---------------------------------------------------------------"
echo ""

[ "$BUILD_CLEAN" = "YES" ] && (rm -rf $BUILD_DIR) && (rm -rf ${INSTALL_PREFIX})

CMAKE_BUILD_OPTION="-DCMAKE_PREFIX_PATH=${QT_PATH}
                    -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
                    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}
                    -DBUILD_VERSION=${BUILD_VERSION}
                    -DBUILD_DOC=${BUILD_DOC}
                    -DBUILD_TEST=${BUILD_TEST}
                    -DBUILD_SHARED_LIBS=${BUILD_SHARE}"

cmake -B ${BUILD_DIR} ${CMAKE_BUILD_OPTION}

cmake --build ${BUILD_DIR} --target install --parallel 4