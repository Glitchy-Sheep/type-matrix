import configure_release
import os

print("-"*20)
print("Building process:")
print("-"*20)

os.chdir(configure_release.build_directory)
os.system("cmake --build . --config Debug")