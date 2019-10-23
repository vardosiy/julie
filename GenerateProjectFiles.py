import os
import sys
import platform

sys.path.insert(1, "scripts/python")

from FilterData import FilterData
from GenerationHelpers import *

#------------------------------------------------------------------------------

filters = list()
filters.append(FilterData("sources", "InitSources.cmake", [".hpp",".cpp"]))
filters.append(FilterData("resources", "InitResources.cmake", [".qrc"]))
filters.append(FilterData("ui_sources", "InitUiSources.cmake", [".qml"]))

targets_dirs = list()
targets_dirs.append("src/utils")
targets_dirs.append("src/core")
targets_dirs.append("src/application")
targets_dirs.append("src/tests/utils_tests")

build_dir = "build"

#------------------------------------------------------------------------------

generate_files_lists(filters, targets_dirs)
generate_prj_files(build_dir)

#------------------------------------------------------------------------------
