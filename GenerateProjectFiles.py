import os
import sys
import platform

sys.path.insert(1, "scripts/python")

from scripts.python.FilesListsGenerator import FilesListsGenerator
from scripts.python.FilterData import FilterData

#------------------------------------------------------------------------------

build_dir = "build"

targets_dirs = list()
targets_dirs.append("src/utils")
targets_dirs.append("src/core")
targets_dirs.append("src/application")

filters = list()
filters.append(FilterData("sources", "InitSources.cmake", [".hpp",".cpp"]))
filters.append(FilterData("resources", "InitResources.cmake", [".qrc"]))
filters.append(FilterData("ui_sources", "InitUiSources.cmake", [".qml"]))

#------------------------------------------------------------------------------

for target_dir in targets_dirs:
	generator = FilesListsGenerator(os.path.normpath(target_dir))
	for filter in filters:
		generator.add_filter(filter)
	generator.generate_files_list()

if not os.path.exists(build_dir):
	os.mkdir(build_dir)

os.chdir(build_dir)
os.system("cmake ..")

#------------------------------------------------------------------------------
