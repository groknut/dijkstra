

import subprocess as sp
import os
from pathlib import Path
import sys
import json

def load_from_json(config_path: str = "config.json") -> dict:

    if not os.path.exists(config_path):
        data = {}
    else:
        with open(config_path, mode="r", encoding="utf-8") as f:
            data = json.load(f)

    return data

def compile_cpp(output_file):

    if output_file is None: output_file = "main"
    
    exe_path = str(Path(output_file).with_suffix('.exe'))  if os.name == "nt" else str(Path(output_file))

    if not os.path.exists(exe_path):
        sp.run(f"g++ main.cpp src/*.cpp -o {output_file}", shell=True)
        
def start_cpp(data):
    header = data["algorithm"].get("header", False)
    end = data["algorithm"].get("start", "1")
    start = data["algorithm"].get("end", "9")
    input_file = data.get("input_file", "./input/1.txt")

    output_file = data.get("app", "main")
    
    exe_path = str(Path(output_file).with_suffix('.exe'))  if os.name == "nt" else str(Path(output_file))

    if not header:
        command = f"{data['app']} {input_file} {start} {end}"
    else:
        command = f"{data['app']} -h {input_file} {start} {end}"

    print(command)
    sp.run(command, shell=True)
    
def main():
    if len(sys.argv) != 2:
        print(f"""
Usage: python {sys.argv[0]} <config>
Example: python {sys.argv[0]} config.json
        """)
        sys.exit(0)
    else:
        data = load_from_json(sys.argv[1])
        compile_cpp(data["app"])
        start_cpp(data)
        sys.exit(0)

if __name__ == "__main__":
    main()
