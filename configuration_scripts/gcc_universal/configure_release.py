import os
import platform
from pathlib import Path


configuration_script_path = Path(os.path.realpath(__file__)).parent
sources_directory = Path(configuration_script_path).parent.parent.absolute()
build_directory = str(sources_directory) + os.sep + "build"

print("-"*22)
print("Configuration process:")
print("-"*22)

print("Configuration directory:\t", configuration_script_path)
print("Sources directory:      \t", sources_directory)
print("Build directory:        \t", build_directory)

CONAN_INSTALL_CMD =  'conan install .' + os.sep
CONAN_INSTALL_CMD += "conanfile_{0}.txt ".format(platform.system().lower())
CONAN_INSTALL_CMD += ' --build missing '
CONAN_INSTALL_CMD += ' -s build_type=Release '
CONAN_INSTALL_CMD += ' -s compiler=gcc '
CONAN_INSTALL_CMD += ' -s compiler.libcxx=libstdc++11 '
CONAN_INSTALL_CMD += ' -s compiler.version=8.1\n'


print("-"*22)
print("Setting up conan:")
print("-"*22)
print(CONAN_INSTALL_CMD)

os.chdir(sources_directory)
os.system(CONAN_INSTALL_CMD)



print("-"*22)
print("CMake generation:")
print("For", platform.system(), "system")
print("-"*22)

if not(os.path.exists(build_directory)):
    os.mkdir(build_directory)

if platform.system() == "Windows":
    CMAKE_GENERATION_CMD = 'cmake -G "MinGW Makefiles" ..'
else:
    CMAKE_GENERATION_CMD = 'cmake -G "Unix Makefiles" ..'

os.chdir(build_directory)
os.system(CMAKE_GENERATION_CMD)
