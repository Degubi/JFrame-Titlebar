from subprocess import call
from os import remove, environ, path, makedirs
from shutil import move
from sys import argv

JAVA_HOME = environ.get('JAVA_HOME')
VCVARS_FILE_DIR = 'Enterprise' if '-actions' in argv else 'Community'
BUILD_COMMAND = f'cl /LD /MD /Od /I "{JAVA_HOME}/include" /I "{JAVA_HOME}/include/win32" titlebar.c User32.lib Dwmapi.lib "{JAVA_HOME}/lib/jawt.lib"'


call(f'"C:/Program Files (x86)/Microsoft Visual Studio/2019/{VCVARS_FILE_DIR}/VC/Auxiliary/Build/vcvars64.bat" && ' + BUILD_COMMAND)
remove('titlebar.obj')
remove('titlebar.exp')
remove('titlebar.lib')

if not path.exists('./src/main/resources'):
    makedirs('./src/main/resources')

move('titlebar.dll', './src/main/resources/JFrameTitlebar.dll')