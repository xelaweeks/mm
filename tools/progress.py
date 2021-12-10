#!/usr/bin/env python3
import argparse, csv, git, json, os, re, sys

parser = argparse.ArgumentParser()

parser = argparse.ArgumentParser(description="Computes current progress throughout the whole project.")
parser.add_argument("format", nargs="?", default="text", choices=["text", "csv", "shield-json"])
parser.add_argument("-m", "--matching", dest='matching', action='store_true',
                    help="Output matching progress instead of decompilation progress")
args = parser.parse_args()

NON_MATCHING_PATTERN = r'#ifdef\s+NON_MATCHING.*?#pragma\s+GLOBAL_ASM\s*\(\s*"(.*?)"\s*\).*?#endif'
NOT_ATTEMPTED_PATTERN = r'#pragma\s+GLOBAL_ASM\s*\(\s*"(.*?)"\s*\)'

# TODO: consider making this a parameter of this script
GAME_VERSION = "mm.us.rev1"

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def GetFunctionsByPattern(pattern, files):
    functions = []

    for file in files:
        with open(file) as f:
            functions += re.findall(pattern, f.read(), re.DOTALL)

    return functions

def ReadAllLines(fileName):
    line_list = list()
    with open(fileName) as f:
        line_list = f.readlines()

    return line_list

def GetFiles(path, ext):
    files = []

    for r, d, f in os.walk(path):
        for file in f:
            if file.endswith(ext):
                files.append(os.path.join(r, file))

    return files

def GetCsvFilelist(version, filelist):
    path = os.path.join("tools", "filelists", version, filelist)
    with open(path, newline='') as f:
        return list(csv.reader(f, delimiter=','))

def GetRemovableSize(functions_to_count):
    size = 0

    for asm_file_path in functions_to_count:
        if "//" in asm_file_path:
            raise RuntimeError(f"Invalid file path: {asm_file_path}")
        file_size = 0
        asm_lines = ReadAllLines(asm_file_path)
        shouldCount = True

        for asm_line in asm_lines:
            if asm_line[0] == ".":
                if asm_line.startswith(".text") or asm_line.startswith(".section .text"):
                    shouldCount = True
                elif ".rdata" in asm_line or ".late_rodata" in asm_line:
                    shouldCount = False

            if shouldCount:
                if (asm_line[0:2] == "/*" and asm_line[28:30] == "*/"):
                    file_size += 4

        size += file_size

    return size

map_file = ReadAllLines('build/mm.map')

# Get list of Non-Matchings
all_files = GetFiles("src", ".c")
non_matching_functions = GetFunctionsByPattern(NON_MATCHING_PATTERN, all_files)

# Get list of functions not attempted.
not_attempted_functions = GetFunctionsByPattern(NOT_ATTEMPTED_PATTERN, all_files)
not_attempted_functions = list(set(not_attempted_functions).difference(non_matching_functions))

# If we are looking for a count that includes non-matchings, then we want to set non matching functions list to empty.
# We want to do this after not attempted functions list generation so we can remove all non matchings.
if not args.matching:
    non_matching_functions = []

assetsCategories = [
    "archive",
    "audio",
    "deleted",
    "interface",
    "misc",
    "objects",
    "scenes",
    "segment",
    "text",
]
assetsTracker = dict()

for assetCat in assetsCategories:
    assetsTracker[assetCat] = dict()
    # Get asset files
    assetsTracker[assetCat]["files"] = GetCsvFilelist(GAME_VERSION, f"{assetCat}.csv")
    assetsTracker[assetCat]["currentSize"] = 0
    assetsTracker[assetCat]["totalSize"] = 0
    assetsTracker[assetCat]["percent"] = 0


# Initialize all the code values
src = 0
src_code = 0
src_boot = 0
src_ovl = 0
src_libultra = 0
asm = 0
asm_code = 0
asm_boot = 0
asm_ovl = 0
asm_libultra = 0

for line in map_file:
    line_split =  list(filter(None, line.split(" ")))

    if (len(line_split) == 4 and line_split[0].startswith(".")):
        section = line_split[0]
        file_size = int(line_split[2], 16)
        obj_file = line_split[3]

        if (section == ".text"):
            if (obj_file.startswith("build/src")):
                if (obj_file.startswith("build/src/code")):
                    src_code += file_size
                elif (obj_file.startswith("build/src/libultra")):
                    src_libultra += file_size
                elif (obj_file.startswith("build/src/boot")):
                    src_boot += file_size
                elif (obj_file.startswith("build/src/overlays")):
                    src_ovl += file_size
            elif (obj_file.startswith("build/asm")):
                if (obj_file.startswith("build/asm/code")):
                    asm_code += file_size
                elif (obj_file.startswith("build/asm/libultra")):
                    asm_libultra += file_size
                elif (obj_file.startswith("build/asm/boot")):
                    asm_boot += file_size
                elif (obj_file.startswith("build/asm/overlays")):
                    asm_ovl += file_size

        if (section == ".data"):
            if (obj_file.startswith("build/assets/")):
                assetCat = obj_file.split("/")[2]
                if assetCat in assetsTracker:
                    assetsTracker[assetCat]["currentSize"] += file_size
                else:
                    eprint(f"Found file '{obj_file.strip()}' in unknown asset category '{assetCat}'")
                    eprint("I'll ignore this for now, but please fix it!")

# Add libultra to boot.
src_boot += src_libultra
asm_boot += asm_libultra

# Calculate Non-Matching
non_matching_functions_ovl = list(filter(lambda x: "/overlays/" in x, non_matching_functions))
non_matching_functions_code = list(filter(lambda x: "/code/" in x, non_matching_functions))
non_matching_functions_boot = list(filter(lambda x: "/boot/" in x, non_matching_functions))

non_matching_asm_ovl = GetRemovableSize(non_matching_functions_ovl)
non_matching_asm_code = GetRemovableSize(non_matching_functions_code)
non_matching_asm_boot = GetRemovableSize(non_matching_functions_boot)

# Calculate Not Attempted
not_attempted_functions_ovl = list(filter(lambda x: "/overlays/" in x, not_attempted_functions))
not_attempted_functions_code = list(filter(lambda x: "/code/" in x, not_attempted_functions))
not_attempted_functions_boot = list(filter(lambda x: "/boot/" in x, not_attempted_functions))

not_attempted_asm_ovl = GetRemovableSize(not_attempted_functions_ovl)
not_attempted_asm_code = GetRemovableSize(not_attempted_functions_code)
not_attempted_asm_boot = GetRemovableSize(not_attempted_functions_boot)

# All the non matching asm is the sum of non-matching code
non_matching_asm = non_matching_asm_ovl + non_matching_asm_code + non_matching_asm_boot

# All the not attempted asm is the sum of not attemped code
not_attempted_asm = not_attempted_asm_ovl + not_attempted_asm_code + not_attempted_asm_boot

# Calculate total decompiled for each bucket by taking out the non-matching and not attempted in ovl/code/boot buckets.
code = src_code - (non_matching_asm_code + not_attempted_asm_code)
boot = src_boot - (non_matching_asm_boot + not_attempted_asm_boot)
ovl = src_ovl - (non_matching_asm_ovl + not_attempted_asm_ovl)

# Total code bucket sizes
code_size = src_code + asm_code
boot_size = src_boot + asm_boot
ovl_size = src_ovl + asm_ovl
handwritten = 0 # Currently unsure of any handwritten asm in MM

# Calculate size of all assets
for assetCat in assetsTracker:
    for index, f in assetsTracker[assetCat]["files"]:
        assetsTracker[assetCat]["totalSize"] += os.stat(os.path.join("baserom", f)).st_size

# Calculate asm and src totals
src = src_code + src_boot + src_ovl
asm = asm_code + asm_boot + asm_ovl

# Take out the non-matchings and not attempted in grand totals
src -= non_matching_asm + not_attempted_asm
asm += non_matching_asm + not_attempted_asm

# Calculate the total amount of decompilable code
total = src + asm

# Calculate assets totals
assets = sum(x["currentSize"] for x in assetsTracker.values())
assets_total = sum(x["totalSize"] for x in assetsTracker.values())

# Convert vaules to percentages
src_percent = 100 * src / total
asm_percent = 100 * asm / total
code_percent = 100 * code / code_size
boot_percent = 100 * boot / boot_size
ovl_percent = 100 * ovl / ovl_size

assets_percent = 100 * assets / assets_total

for assetCat in assetsTracker:
    assetsTracker[assetCat]["percent"] = 100 * assetsTracker[assetCat]["currentSize"] / assetsTracker[assetCat]["totalSize"]

# convert bytes to masks and rupees
num_masks = 24
max_rupees = 500
bytes_per_mask = total / num_masks
bytes_per_rupee = bytes_per_mask / max_rupees
masks = int(src / bytes_per_mask)
rupees = int((src % bytes_per_mask) / bytes_per_rupee)

# Debug print statements for the values
#print("Total: ", total)
#print("src: ", src)
#print("asm: ", asm)
#print("")
#print("src_code: ", src_code)
#print("src_boot: ", src_boot)
#print("src_ovl: ", src_ovl)
#print("")
#print("asm_code: ", asm_code)
#print("asm_boot: ", asm_boot)
#print("asm_ovl: ", asm_ovl)
#print("")
#print("Nonmatching code: ", non_matching_asm_code)
#print("Nonmatching boot: ", non_matching_asm_boot)
#print("Nonmatching ovl: ", non_matching_asm_ovl)
#print("")
#print("Not attempted code: ", not_attempted_asm_code)
#print("Not attempted boot: ", not_attempted_asm_boot)
#print("Not attempted ovl: ", not_attempted_asm_ovl)
#print("")
#print("code_size: ", code_size)
#print("boot_size: ", boot_size)
#print("ovl_size: ", ovl_size)
#print("")
#print("code: ", code)
#print("boot: ", boot)
#print("ovl: ", ovl)
#print("")

if args.format == 'csv':
    version = 2
    git_object = git.Repo().head.object
    timestamp = str(git_object.committed_date)
    git_hash = git_object.hexsha
    csv_list = [
        version, timestamp, git_hash, src, total,
        boot, boot_size, code, code_size, ovl, ovl_size,
    ]
    csv_list += [
        assets, assets_total,
    ]
    for assetCat in assetsCategories:
        csv_list += [assetsTracker[assetCat]["currentSize"], assetsTracker[assetCat]["totalSize"]]

    print(",".join(map(str, csv_list)))
elif args.format == 'shield-json':
    # https://shields.io/endpoint
    print(json.dumps({
        "schemaVersion": 1,
        "label": "progress",
        "message": f"{src_percent:.3g}%",
        "color": 'yellow',
    }))
elif args.format == 'text':
    adjective = "decompiled" if not args.matching else "matched"

    print("src:  {:>9} / {:>8} total bytes {:<13} {:>9.4f}%".format(src, total, adjective, round(src_percent, 4)))
    print("    boot:      {:>9} / {:>8} bytes {:<13} {:>9.4f}%".format(boot, boot_size, adjective, round(boot_percent, 4)))
    print("    code:      {:>9} / {:>8} bytes {:<13} {:>9.4f}%".format(code, code_size, adjective, round(code_percent, 4)))
    print("    overlays:  {:>9} / {:>8} bytes {:<13} {:>9.4f}%".format(ovl, ovl_size, adjective, round(ovl_percent, 4)))
    print()

    print("assets:     {:>9} / {:>8} bytes reconstructed {:>9.4f}%".format(assets, assets_total, round(assets_percent, 4)))
    for assetCat in assetsTracker:
        data = assetsTracker[assetCat]
        print("    {:<10} {:>9} / {:>8} bytes reconstructed {:>9.4f}%".format(f"{assetCat}:", data["currentSize"], data["totalSize"], round(data["percent"], 4)))

    print()
    print("------------------------------------\n")

    if (rupees > 0):
        print('You have {}/{} masks and {}/{} rupee(s).\n'.format(masks, num_masks, rupees, max_rupees))
    else:
        print('You have {}/{} masks.\n'.format(masks, num_masks))
else:
    print("Unknown format argument: " + args.format)
