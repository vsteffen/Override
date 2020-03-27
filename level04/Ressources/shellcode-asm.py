from sys import argv

import subprocess   # Popen, PIPE, call
import tempfile     # Get random names for temp files
import os           # path functions, remove function
import re           # regular expression matching

# Supported architectures by this code, you can add more
architectures = {
    "32": "elf_i386",
    "64": "elf_x86_64"
}

def nasm(in_file, arch):
    '''
        Assemble in_file to object file using a specific architecture, nasm is
        required to be installed for this function.
    '''

    temp_object = "/tmp/" + next(tempfile._get_candidate_names())
    subprocess.call(["nasm", "-f", "elf" + arch, "-o", temp_object, in_file])
    return temp_object

def ld(in_file, arch):
    '''
        System linker; convert the object file to an executable that has the right
        offsets. We'll be disassembling the output of ld.
    '''

    arch = architectures[arch]
    temp_output = "/tmp/" + next(tempfile._get_candidate_names())
    subprocess.call(["ld", "-m", arch, "-o", temp_output, in_file])
    return temp_output

def objdump(in_file):
    '''
        objdump disassembles our resulting binary and produces a string that can
        be used in Python or Bash to inject into the target process
    '''

    process         = subprocess.Popen(["objdump", "-d", in_file], stdout=subprocess.PIPE)
    (output, error) = process.communicate()
    exit_code       = process.wait()
    output          = output.decode("utf-8")
    result          = ""

    # pattern1: match each line of assembly up to the assembly syntax
    pattern1 = re.compile(r'\s+([0-9a-f]+):\s*([0-9a-f ]+)\s{2}')
    pattern2 = re.compile(r'([0-9a-f]+)\s{1}')

    # find each line with instructions
    for (address, match) in re.findall(pattern1, output):
        # find each opcode in hex representation
        for opcode in re.findall(pattern2, match):
            result += "\\x" + opcode

    # return nice hex encoded machinecode
    return result

# determine number of cli arguments
argc = len(argv)

# at least the input file is required
if (argc < 2):
    print("error: a minimum of 1 argument is required for this command")
    exit()

in_file = argv[1]

# default to 32-bit, allow 64-bit
arch = "32"
if (argc >= 3):
    arch = argv[2]

if (arch != "32" and arch != "64"):
    print("error: invalid architecture, only 32 or 64 are supported right now")
    exit()

# assemble code, produce executable with .text section and extract that as binary
object_file = nasm(in_file, arch)
output_file = ld(object_file, arch)
output_hexs = objdump(output_file)

# display string that is usable in bash and python 
print("\"" + output_hexs + "\"")

# clean up
for f in [object_file, output_file]:
    if (os.path.isfile(f)):
        os.remove(f)