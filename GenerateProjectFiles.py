import os
import sys
import platform

sys.path.insert(1, "scripts/python")

from scripts.python.FilesListsGenerator import FilesListsGenerator
from scripts.python.FilterData import FilterData

#------------------------------------------------------------------------------

def generate_files_lists(filters, targets_dirs):
	generator = FilesListsGenerator()

	for filter in filters:
		generator.add_filter(filter)

	for target_dir in targets_dirs:
		generator.generate_files_list(os.path.normpath(target_dir))

#------------------------------------------------------------------------------

def generate_prj_files(build_dir):
	if not os.path.exists(build_dir):
		os.mkdir(build_dir)

	os.chdir(build_dir)
	os.system("cmake ..")

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
