import os
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

CONAN_INSTALL_CMD =  'conan install .' + os.sep + "conanfile_windows.txt "
CONAN_INSTALL_CMD += ' --build missing '
CONAN_INSTALL_CMD += ' -s build_type=Release '
CONAN_INSTALL_CMD += ' -s compiler="Visual Studio" '
CONAN_INSTALL_CMD += ' -s compiler.cppstd=17 '
CONAN_INSTALL_CMD += ' -s compiler.runtime=MT '
CONAN_INSTALL_CMD += ' -s compiler.version=17\n'



print("-"*22)
print("Setting up conan:")
print("-"*22)
print(CONAN_INSTALL_CMD)

os.chdir(sources_directory)
os.system(CONAN_INSTALL_CMD)

if not(os.path.exists(build_directory)):
    os.mkdir(build_directory)



print("-"*22)
print("CMake generation:")
print("-"*22)

CMAKE_GENERATION_CMD = 'cmake -G "Visual Studio 17 2022" ..'
os.chdir(build_directory)
os.system(CMAKE_GENERATION_CMD)