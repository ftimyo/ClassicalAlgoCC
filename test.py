import subprocess
import os
fs = os.listdir('.')
for f in fs:
    if f.endswith('.cc'):
        print(f)
        subprocess.run(['clang++','-std=c++1z',f,'-o','xxxxxox'])
        subprocess.run(['./xxxxxox'])
