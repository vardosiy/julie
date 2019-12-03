import os
import sys
import platform

sys.path.insert(1, "scripts/python")

from FilterData import FilterData
from GenerationHelpers import *

#------------------------------------------------------------------------------

filters = list()
filters.append(FilterData("sources",	"InitSources.cmake",	[".c", ".cpp"]))
filters.append(FilterData("headers",	"InitHeaders.cmake",	[".h", ".hpp"]))
filters.append(FilterData("resources",	"InitResources.cmake",	[".qrc"]))
filters.append(FilterData("shaders",	"InitShaders.cmake",	[".vs", ".fs"]))

targets_dirs = list()
targets_dirs.append("3rd-party/glad")
targets_dirs.append("src/application")
targets_dirs.append("src/renderer")
targets_dirs.append("src/utils")
targets_dirs.append("src/tests/utils_tests")

build_dir = "build"

#------------------------------------------------------------------------------

generate_files_lists(filters, targets_dirs)
generate_prj_files(build_dir)

#------------------------------------------------------------------------------
