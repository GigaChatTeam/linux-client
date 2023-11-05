from typing import *

def find(strings: List[str], start: int, elem: str):
    for i, e in enumerate(strings[start:]):
        if (e.startswith(elem)):
            return i+start;
    return -1;

with open("src/utils/misc_functions.h", "r") as file:
    strings = file.readlines();
    enum_start = find(strings, 0, "enum MessageType") + 1;
    enum_end = find(strings, enum_start, "};");
    array_start = max( \
            find(strings, 0, "constexpr const char"), \
            find(strings, 0, "const char *types[]")) + 1;
    array_end = find(strings, array_start, "};");

    enum_entries = list(filter( \
            lambda x: not "//" in x, \
            strings[enum_start:enum_end]) \
            );
    array_entries = list(map(\
            lambda x: x.replace('\"', "").replace('-', '_'),
            filter( \
                    lambda x: not "//" in x, \
                    strings[array_start:array_end]\
                   ) \
            ));
    
    same: bool = True;
    for i, j in zip(enum_entries, array_entries):
        if (i.strip() != j.strip()):
            print(("DIFF:\n" + \
                   "\x1b[96m%-50s\x1b[91m->\t\x1b[92m%-50s\n" + \
                   "\x1b[1;96m%-50s\x1b[91m->\t\x1b[92m%-50s\n" + \
                   "\x1b[0m") \
                   % ( \
                       "ENUM", "ARRAY", \
                       i.strip(), j.strip() \
                       ) );
            same = False;

    if (same): print("\x1b[93mNo differences spotted!\x1b[0m\n");
    else: print("\x1b[1;91mDifferences spotted!\x1b[0m")
    
