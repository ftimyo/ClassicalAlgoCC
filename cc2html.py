import os
import subprocess
for f in os.listdir():
    if f.endswith('.cc'):
        subprocess.run(['vim','-c','TOhtml','-c','wqa', f])
        nf = f+'.html'
        print(nf)
        subprocess.run(['sed','-i','','15s/1em/115%/',nf])
